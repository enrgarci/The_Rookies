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

Partida P("", "", "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
//Partida P("", "", "r1b1kbnr/1pp2ppp/p1p5/4N3/3qP3/8/PPPP1PPP/RNBQK2R w KQkq - 1 6");
Tablero T = P.getBoard();
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

// Rotate the board depending on whether it is black or white's turn
// Receives the cell number(0 - 63), and the column and row that will be modified
void Interface::rotateBoard(int value, int& col, int& row) 
{
    if (T.get_turn() == Blanco) 
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
void Interface::drawBoard() 
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

    //draw board grid
    for (int col = 0; col < gridSize; col++) 
    {
        for (int row = 0; row < gridSize; row++) 
        {
            if ((row + col) % 2 == 0) 
            {
                glColor3f(0.71, 0.53, 0.37); // color for black squares
            }
            else 
            {
                glColor3f(0.94, 0.85, 0.71); // color for white squares
            }

            glBegin(GL_QUADS);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
            glEnd();
        }
    }
}

// Draws the pieces on the board
void Interface::drawPieces() 
{
    std::string skin = "skin_default";
    std::string figure = "";
    std::string color = "";
    std::string direction = "";

    for (int i = 0; i <64; i++) 
    {
        int col;
        int row;
        rotateBoard(i, col, row);

        switch (T[i].getPiece().getFig()) 
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

        switch (T[i].getPiece().getColor()) 
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
// Draws green transparent squares on the board at the corresponding locations
void Interface::drawPossibleMoves(std::vector<int>& move_list) 
{
    for (auto i:move_list) 
    {
        int col;
        int row;

        rotateBoard(i, col, row);
      
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glColor4f(0, 1, 0, 0.5);
        glBegin(GL_QUADS);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
        glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
        glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
        glEnd();
       
        glDisable(GL_BLEND);
    }
}

// Handles user input and updates the interface based on the game's state
// Checks the value of a variable called click_flag, which keeps track of the number of clicks made by the user on the chessboard.
// Depending on the value of click flag, and the selected cell, the necessary functions are called to update the interface
void Interface::drawMovement() 
{    
    static std::vector<int> move_list;
    static int first_cell;
    static color first_piece_color;

    if (T.get_turn() == Negro)
    {
        IA.randommove(T, Negro);
        T.move_count++;
        S.play("Move_Piece");
        drawBoard();
        drawPieces();
    }

    switch (click_flag) 
    {
    // No click has been detected on the board grid, or after two consecutive clicks if color is not repeated
    case 0:
        break;
    // One click has been detected on the board grid
    case 1: 
        // Empty cell
        if (T[cell_number].getPiece().getFig() == Vacio)    
        {
            click_flag = 0;
            break;
        }
        // Select piece
        move_list = T[cell_number].getMoveList(T);
        first_piece_color = T[cell_number].getPiece().getColor();
        first_cell = cell_number;
        // Only allows to select a piece if the turn is equal to the piece clicked
        if (T.get_turn() != first_piece_color) {
            click_flag = 0;
            break;
        }
        drawBoard();
        drawPossibleMoves(move_list);
        drawPieces();
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
        if (first_piece_color == T[cell_number].getPiece().getColor()) 
        {
            click_flag = 1;
            move_list = T[cell_number].getMoveList(T);
            first_cell = cell_number;
            drawBoard();
            drawPossibleMoves(move_list);
            drawPieces();
            break;
        }
        for (int i = 0; i < move_list.size(); i++) 
        {
            // Selected possible move - redraw board and pieces
            if (cell_number == move_list[i]) 
            {
                click_flag = 0;
                //aqui irá la funcion que llame a la logica para modificar la posicion del tablero
                T.do_move(first_cell, cell_number);
                T.move_count++;
                //board and pieces are drawn again
                drawBoard();
                drawPieces();
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
void Interface::mouseBoard(int button, int state, int x, int y) 
{
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
}