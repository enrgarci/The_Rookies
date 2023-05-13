#include "Interface.h"
#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include <string.h>

#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"
#include "SoundController.h"
#include "AI.h"

Partida P("", "");
//Partida P("", "", "r1b1kbnr/1pp2ppp/p1p5/4N3/3qP3/8/PPPP1PPP/RNBQK2R w KQkq - 1 6");
SoundController S;
AI IA;

// Initializes interface attributes related to the screen and its coordinates
void Interface::init()
{
    // Set screen dimensions
    gridSize = 8;
    fullscreen = true;
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    // Set board size as the minimum between the width and height of the screen
    board_size = min(screen_width, screen_height);
    float reduction = 0.6;
    board_size *= reduction; // the size of the board is reduced to leave a margin

    // Set coordinates of the botton left corner of the board grid
    board_origin_x = (screen_width - board_size) / 2;
    board_origin_y = (screen_height - board_size) / 2;

    // Set square size based on board size and grid size
    square_size = board_size / gridSize;

    // Set coordinates of the botton left corner of each square (divided by screen height)
    for (int col = 0; col < gridSize; col++)
    {
        for (int row = 0; row < gridSize; row++)
        {
            grid_coordinates[col][row] = { (board_origin_x + col * square_size) / screen_height ,
                                           (board_origin_y + row * square_size) / screen_height };
        }
    }
    S.playMusica("MainBGM", true);
    S.play("Board_Start");

    //Set initial position for the clock
    theta = 0;
}

Interface::coordinate Interface::getGridCoordinate(int col, int row)
{
    return grid_coordinates[col][row];
}

// Takes as parameter the cell number from 0 to 63, with origin (0,0) bottom left (a1)
// Modify the cell number, with origin at the top left (a8)
// Depends on whether the board should be rotated that turn
void Interface::changeOrigin(int& value)
{
    int col;
    int row;
    rotateBoard(value, col, row);
    value = 8 * row + col;
}

// Rotate the board depending on whether it is black or white's turn, or if the board must be rotated
// Receives the cell number(0 - 63), and the column and row that will be modified
void Interface::rotateBoard(int value, int& col, int& row)
{
    if (P.T->get_turn() == Blanco || doRotate == false)
    {
        col = value % 8;
        row = 7 - (value / 8);
    }
    else
    {
        col = 7 - (value % 8);
        row = (value / 8);
    }
}

// Draws the border and grid of the board
void Interface::drawBoard(int EstadoSkin)
{
    glClearColor(0.03f, 0.52f, 0.11f, 0.5f); // background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw board border
    float k = 1.2;  //coeficient to draw the board border bigger than the grid
    float border_size = k * board_size;
    float x_border = ((screen_width - border_size) / 2) / screen_height;    //X coordinate of the bottom left corner of the border, divided by screen height
    float y_border = ((screen_height - border_size) / 2) / screen_height;   //Y coordinate of the bottom left corner of the border, divided by screen height
    glColor3f(0.20, 0.15, 0.1); //board edge color 
    glBegin(GL_QUADS);
    glVertex2f(x_border, y_border);
    glVertex2f(x_border + border_size / screen_height, y_border);
    glVertex2f(x_border + border_size / screen_height, y_border + border_size / screen_height);
    glVertex2f(x_border, y_border + border_size / screen_height);
    glEnd();

    switch (EstadoSkin)
    {
    case 1: br = 0.71; bg = 0.53; bb = 0.37; wr = 0.94; wg = 0.85; wb = 0.71; break; //Default
    case 2: br = 0.1; bg = 0.275; bb = 0.1; wr = 0.4; wg = 0.9; wb = 0.4; break;    //Pvs>Z
    case 3: br = 0.87; bg = 0.16; bb = 0.19; wr = 0.71; wg = 0.81; wb = 1; break;      //SW
    }
    

    //draw board grid
    for (int col = 0; col < gridSize; col++)
    {
        for (int row = 0; row < gridSize; row++)
        {
            if ((row + col) % 2 == 0)
            {
                glColor3f(br, bg, bb); // color for black squares
            }
            else
            {
                glColor3f(wr, wg, wb); // color for white squares
            }

            glBegin(GL_QUADS);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
            glEnd();
        }
    }
    if (nanoState()) 
    {    
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/33.png").id);

        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glTexCoord2d(0, 1);     glVertex2f(grid_coordinates[0][0].x, grid_coordinates[0][0].y);
        glTexCoord2d(1, 1);     glVertex2f(grid_coordinates[0][0].x + board_size / screen_height, grid_coordinates[0][0].y);
        glTexCoord2d(1, 0);     glVertex2f(grid_coordinates[0][0].x + board_size / screen_height, grid_coordinates[0][0].y + board_size / screen_height);
        glTexCoord2d(0, 0);     glVertex2f(grid_coordinates[0][0].x, grid_coordinates[0][0].y + board_size / screen_height);
        glEnd();

        glDisable(GL_TEXTURE_2D);

    }
}

// Draws the pieces on the board
void Interface::drawPieces(int EstadoSkin)
{
    std::string skin = "skin_default";
    std::string figure = "";
    std::string color = "";
    std::string direction = "";

    switch (EstadoSkin)
    {
    case 1: skin = "skin_default"; break;
    case 2: skin = "skin_pvsz"; break;
    case 3: skin = "skin_sw"; break;
    }

    for (int i = 0; i < 64; i++)
    {
        int col;
        int row;
        rotateBoard(i, col, row);

        switch (P.T->get_cell(i).getFigura())
        {
        case  Vacio:
            figure = "vacio";
            break;
        case Rey:
            figure = "rey";
            break;
        case Reina:
            figure = "reina";
            break;
        case Torre:
            figure = "torre";
            break;
        case Alfil:
            figure = "alfil";
            break;
        case Caballo:
            figure = "caballo";
            break;
        case Peon:
            figure = "peon";
            break;
        }

        switch (P.T->get_cell(i).getColor())
        {
        case noColor:
            break;
        case Blanco:
            color = "blanco";
            break;
        case Negro:
            color = "negro";
            break;
        }

        if (figure == "vacio") continue;

        direction = "imagenes/" + skin + "/" + color + "/" + figure + ".png";
        const char* texture_path = direction.c_str();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(texture_path).id);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDepthFunc(GL_LESS);

        glBegin(GL_QUADS);
        glColor3f(1, 1, 1);
        glTexCoord2d(0, 1);     glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
        glTexCoord2d(1, 1);     glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
        glTexCoord2d(1, 0);     glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
        glTexCoord2d(0, 0);     glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
        glEnd();

        glDepthFunc(GL_LEQUAL);
        glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    }

}

// Takes a vector of integers 'move_list' as input, which represent the valid moves in the game for a given cell
// Draws semi-transparent squares on the board at the corresponding locations
void Interface::drawPossibleMoves(std::vector<int>& move_list)
{
    for (auto i : move_list)
    {
        int col;
        int row;

        rotateBoard(i, col, row);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0.5, 0.8, 0.93, 0.5);
        glBegin(GL_QUADS);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
        glEnd();

        glDisable(GL_BLEND);
    }
}

void Interface::drawCoronation(int EstadoSkin, int cell, std::vector<int>& move_list)
{
    //si el peon puede coronar en la siguiente jugada
    if (P.T->get_cell(cell).getFigura() == Peon &&
        ((P.T->get_cell(cell).getColor() == Negro && cell >= 48) ||
            P.T->get_cell(cell).getColor() == Blanco && cell <= 15))
    {
        const int PiecesCor[4] = { Reina, Torre, Alfil, Caballo };
        std::string skin = "skin_default";
        std::string figure = "";
        std::string color = "";
        std::string direction = "";

        switch (EstadoSkin)
        {
        case 1: skin = "skin_default"; break;
        case 2: skin = "skin_pvsz"; break;
        case 3: skin = "skin_sw"; break;
        }

        for (auto i : move_list)
        {
            int col;
            int row;

            rotateBoard(i, col, row);

            switch (CorIndex)
            {
            case 0:
                figure = "reina";
                break;
            case 1:
                figure = "torre";
                break;
            case 2:
                figure = "alfil";
                break;
            case 3:
                figure = "caballo";
                break;
            }

            switch (P.T->get_cell(cell).getColor())
            {
            case noColor:
                break;
            case Blanco:
                color = "blanco";
                break;
            case Negro:
                color = "negro";
                break;
            }

            if (figure == "vacio") continue;

            direction = "imagenes/" + skin + "/" + color + "/" + figure + ".png";
            const char* texture_path = direction.c_str();

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture(texture_path).id);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glDepthFunc(GL_LESS);

            glBegin(GL_QUADS);
            glColor3f(1, 1, 1);
            glTexCoord2d(0, 1);     glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
            glTexCoord2d(1, 1);     glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
            glTexCoord2d(1, 0);     glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
            glTexCoord2d(0, 0);     glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
            glEnd();

            glDepthFunc(GL_LEQUAL);
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        }
    }
}

// Draws the last move made on the board
// Takes a vector of two elements: the cell of origin and destination of the movement
// Checks if those two cells match any of the valid moves, if they don't match, draws a semi-transparent yellow square in the corresponding locations
void Interface::drawLastMove(int *movement, std::vector<int>& move_list, bool check_list)
{
    if (P.T->move_count == 0) return;

    for (int i = 0; i < 2; i++)
    {
        if (check_list)
        {
            bool cell_flag = false;
            for (auto j : move_list) if (j == movement[i]) cell_flag = true;
            if (cell_flag == true) continue;
        }

        int col;
        int row;

        rotateBoard(movement[i], col, row);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(1, 1, 0, 0.5);
        glBegin(GL_QUADS);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
        glEnd();

        glDisable(GL_BLEND);
    }
}

bool Interface::nanoState(int key)
{
    static bool state = false;
    static int value = 0;
    if (key == 0) return state;
    if (key != '3') value = 0;
    else if (key == '3' && value == 0) value = 1;
    else if (key == '3' && value == 1) {
        value = 0;
        state = state == false ? true : false;
    }
    return state;
}

// Handles user input and updates the interface based on the game's state
// Checks the value of a variable called click_flag, which keeps track of the number of clicks made by the user on the chessboard.
// Depending on the value of click flag, and the selected cell, the necessary functions are called to update the interface
void Interface::drawMovement(int EstadoSkin)
{
    int eventSound;
    static std::vector<int> move_list;
    static int first_cell;
    static color first_piece_color;
    static int movement[2];

    drawBoard(EstadoSkin);
    drawLastMove(movement, move_list, false);
    drawPieces(EstadoSkin);
    drawButtons();
    // Pending of review, because it doesnt work with the move backwards and forwards
    /*if (P.T->get_turn() == Negro)
    {
        IA.randommove(*(P.T), Negro);
        S.play("Move_Piece");
        drawBoard();
        drawPieces();
    }*/
    
    switch (click_flag) 
    {
    // No click has been detected on the board grid, or after two consecutive clicks if color is not repeated
    case 0:
        break;
    // One click has been detected on the board grid
    case 1:
        // Empty cell
        if (P.T->get_cell(cell_number).getColor() == Vacio)
        {
            click_flag = 0;
            break;
        }
        // Select piece
        move_list = P.T->get_cell(cell_number).getMoveList();
        first_piece_color = P.T->get_cell(cell_number).getColor();
        first_cell = cell_number;
        // Only allows to select a piece if the turn is equal to the piece clicked
        if (P.T->get_turn() != first_piece_color) {
            click_flag = 0;
            break;
        }
        drawBoard(EstadoSkin);
        drawLastMove(movement, move_list, true);
        drawPossibleMoves(move_list);
        drawPieces(EstadoSkin);
        drawCoronation(EstadoSkin ,cell_number, move_list);
        drawButtons();
        break;
    // Two clicks has been detected on the board grid
    case 2:
        // Repeated cell - deselect piece
        if (first_cell == cell_number)
        {
            click_flag = 0;
            break;
        }
        // Piece of the same color - select new piece
        if (first_piece_color == P.T->get_cell(cell_number).getColor())
        {
            click_flag = 1;
            move_list = P.T->get_cell(cell_number).getMoveList();
            first_cell = cell_number;
            drawBoard(EstadoSkin);
            drawLastMove(movement, move_list, true);
            drawPossibleMoves(move_list);
            drawPieces(EstadoSkin);
            drawCoronation(EstadoSkin, cell_number, move_list);
            drawButtons();
            break;
        }
        for (int i = 0; i < move_list.size(); i++)
        {
            // Selected possible move - redraw board and pieces
            if (cell_number == move_list[i])
            {
                click_flag = 0;
                movement[0] = first_cell;
                movement[1] = cell_number;
                //function to modify the board position
                eventSound = (P.T)->do_move(first_cell, cell_number);
                S.playevent(eventSound);
                //board and pieces are drawn again
                drawBoard(EstadoSkin);
                drawLastMove(movement, move_list, false);
                drawPieces(EstadoSkin);
                drawButtons();
                S.play("Move_Piece");
                break;
            }
        }
        // Selected move not allowed - deselect cell
        if (click_flag == 2)
        {
            click_flag = 0;
        }
        break;
    }
}

void Interface::drawButtons()
{
  
    //(1150, 10, 100, 100, 200, 100, 150); (1350, 10, 100, 100, 200, 100, 150);  (600, 10, 100, 100, 200, 100, 150);  (800, 10, 100, 100, 200, 100, 150);
    pauseMenu.Set(10, 750, 100, 100, 200, 100, 150);
    playBackButton.Set(638, 10, 100, 100, 200, 100, 150);
    playForwardButton.Set(798, 10, 100, 100, 200, 100, 150);
    playFirstButton.Set(485, 10, 100, 100, 200, 100, 150);
    playLastButton.Set(950, 10, 100, 100, 200, 100, 150);



    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Pause.png").id);
    pauseMenu.Draw();

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Left-Arrow.png").id);
    playBackButton.Draw();//1 atras

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Right-Arrow.png").id);
    playForwardButton.Draw();//1 adelante

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Right-Double-Arrow.png").id);
    playLastButton.Draw();// actual

    glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Left-Double-Arrow.png").id);
    playFirstButton.Draw();// inicio

   
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    
    reloj(0.85);

}

void Interface::reloj(float theta)
{
    
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.5f);

  //  glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/marco reloj.png").id);
    marco.Set(1215, 530, 150, 150, 200, 200, 200);
    marco.Draw();

    //glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Aguja.png").id);
    aguja.Set(-14, -14, 20, 70, 150, 100, 150);
    float x = 1.5, y = 0.7, a = 1;

    glTranslatef(x, y, 0);
    glRotatef(-theta * 360, 0.0f, 0.0f, 1.0f);
    aguja.Draw();// inicio
    glRotatef(theta * 360, 0.0f, 0.0f, 1.0f);
    glTranslatef(-x, -y, 0);

    
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_ALPHA_TEST);
    glDisable(GL_BLEND);
    

}

void Interface::mouseButtons(int button, int state, int x, int y, int& Estado)
{
    //system("cls");
    //playBackButton, playForwardButton, playLastButton, playFirstButton;
    if (pauseMenu.isInside(button, state, x, y)) submenu(Estado);
    if (playBackButton.isInside(button, state, x, y)) P.play_back();  //1 atras
    if (playForwardButton.isInside(button, state, x, y)) P.play_forward();//1 adelante
    if (playLastButton.isInside(button, state, x, y)) P.play_last(); // actual
    if (playFirstButton.isInside(button, state, x, y)) P.play_first();// inicio

}

// Ensures that the OpenGL scene is adjusted to the new size of the window, maintaining the aspect ratio
void Interface::reshape(int w, int h)
{
    // Defining the viewport and projection
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    {
        glOrtho(0, 1.0, 0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    }
    else
    {
        glOrtho(0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, 0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Handles mouse clicks on the game board and updates the necessary variables to keep track of the state of the game.
void Interface::mouseBoard(int button, int state, int x, int y, int & Estado)
{
 
    mouseButtons( button, state, x, y, Estado);
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        // Convert mouse coordinates to window coordinates
        if (x > board_origin_x && x < board_origin_x + board_size && y < screen_height - board_origin_y && y > board_origin_y)
        {
            float vx = ((float)x - board_origin_x) / board_size;
            float vy = 1.0f - ((float)y - board_origin_y) / board_size;

            // Calculate selected square
            int row = (int)(vy * gridSize);
            int col = (int)(vx * gridSize);

            cell_number = row * 8 + col;
            changeOrigin(cell_number);

            switch (click_flag)
            {
            case 0: //no click has been detected on the board grid
                click_flag = 1;
                break;
            case 1: //one click has been detected on the board grid
                click_flag = 2;
                break;
            case 2: //two clicks has been detected on the board grid
                break;
            }
        }
    }
}

// Handles the keyboard input when the program is in fullscreen mode
// If the program is currently in fullscreen mode, pressing escape will switch to windowed mode, and vice versa.
void Interface::keyboardFullscreen(unsigned char key, int x, int y)
{
    const int PiecesCor[4] = { Reina, Torre, Alfil, Caballo };
    const char ESCAPE_KEY = 27;
    if (key == ESCAPE_KEY)
    {
        if (fullscreen)
        {
            glutReshapeWindow(screen_width, screen_height);
            fullscreen = false;
        }
        else
        {
            glutFullScreen();
            fullscreen = true;
        }
    }
    //nanothings
    nanoState(key);
    //for game review puposes, you can go back and forward
    if (key == 'a')    P.play_back();
    if (key == 'd')    P.play_forward();
    if (key == 'w')    P.play_last();
    if (key == 's')    P.play_first();
    if (key == ' ')
    {
        CorIndex++;
        CorIndex = CorIndex % 4;
        (P.T)->setCoronacion((figura) PiecesCor[CorIndex]);
        cout << CorIndex << endl;
    }
    glutPostRedisplay();
}

void Interface::submenu(int& Estado)
{
    //11 Is the code for the Pause menu (Submenu_menu) in the enum in Menu.h
    Estado = 11;
}