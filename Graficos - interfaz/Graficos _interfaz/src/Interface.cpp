#include "Interface.h"
#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"

void Interface::init() {

    // Set screen dimensions
    gridSize = 8;
    fullscreen = true;
    screen_width = glutGet(GLUT_SCREEN_WIDTH);
    screen_height = glutGet(GLUT_SCREEN_HEIGHT);

    // Set board size as the minimum between the width and height of the screen
    board_size = min(screen_width, screen_height);
    float reduction = 0.6;  //board size relative to the smallest dimension of the screen
    board_size *= reduction; // the size of the board is reduced to leave a margin

    // Set coordinates of the botton left corner of the board grid
    board_origin_x = (screen_width - board_size) / 2;
    board_origin_y = (screen_height - board_size) / 2;

    // Set square size based on board size and grid size
    square_size = board_size / gridSize;

    // Set coordinates of the botton left corner of each square (divided by screen height)
    for (int col = 0; col < gridSize; col++) {
        for (int row = 0; row < gridSize; row++) {
            grid_coordinates[col][row] = { (board_origin_x + col * square_size) / screen_height ,
                                           (board_origin_y + row * square_size) / screen_height };
            std::cout << grid_coordinates[col][row].x << ", " << grid_coordinates[col][row].y << std::endl; //only for testing, will be removed
        }
    }

}

void Interface::drawBoard() {

    glClearColor(0.5f, 0.5f, 0.5f, 0.5f); // background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //draw board border
    float k = 1.2;  //coeficient to draw the board border bigger than the grid
    float border_size = k * board_size;
    float x_border = ((screen_width - border_size) / 2) / screen_height;    //X coordinate of the bottom left corner of the border, divided by screen height
    float y_border = ((screen_height - border_size) / 2) / screen_height;    //Y coordinate of the bottom left corner of the border, divided by screen height
    glColor3f(0.20, 0.15, 0.1); //board edge color 
    glBegin(GL_QUADS);
    glVertex2f(x_border, y_border);
    glVertex2f(x_border + border_size / screen_height, y_border);
    glVertex2f(x_border + border_size / screen_height, y_border + border_size / screen_height);
    glVertex2f(x_border, y_border + border_size / screen_height);
    glEnd();

    //draw board grid
    for (int col = 0; col < gridSize; col++) {
        for (int row = 0; row < gridSize; row++) {

            if ((row + col) % 2 == 0) {
                glColor3f(0.45, 0.3, 0.2); // color for black squares
            }
            else {
                glColor3f(0.9, 0.8, 0.7); // color for white squares
            }

            glBegin(GL_QUADS);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y);
            glVertex2f(grid_coordinates[col][row].x + square_size / screen_height, grid_coordinates[col][row].y + square_size / screen_height);
            glVertex2f(grid_coordinates[col][row].x, grid_coordinates[col][row].y + square_size / screen_height);
            glEnd();
        }
    }

    glutSwapBuffers();
}

void Interface::reshape(int w, int h)
{
    // Update window width and height variables
    //windowWidth = w;
    //windowHeight = h;

    // Defining the viewport and projection
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(0, 1.0, 0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    }
    else {
        glOrtho(0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, 0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Interface::mouseBoard(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Convert mouse coordinates to window coordinates
        if (x > board_origin_x && x < board_origin_x + board_size && y < screen_height - board_origin_y && y > board_origin_y) {
            float vx = ((float)x - board_origin_x) / board_size;
            float vy = 1.0f - ((float)y - board_origin_y) / board_size;

            // Calculate selected square
            int row = (int)(vy * gridSize);
            int col = (int)(vx * gridSize);

            //std::cout << "Casilla seleccionada: (" << col << ", " << row << ")" << std::endl;
            std::cout << "Casilla seleccionada: " << static_cast<char>('a' + col) << row + 1 << std::endl;  //display selected square
        }
    }
}
