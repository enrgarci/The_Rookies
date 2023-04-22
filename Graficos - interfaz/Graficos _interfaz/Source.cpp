#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include "Interface.h"

Interface interfaz;

void onDraw() {
    interfaz.drawBoard();
    interfaz.drawPieces();
    glutSwapBuffers();
}

void onReshape(int w, int h) {
    interfaz.reshape(w, h);
}

void onMouse(int button, int state, int x, int y) {
    interfaz.mouseBoard(button, state, x, y);
}

void onKeyboard(unsigned char key, int x, int y) {
    interfaz.keyboardFullscreen(key, x, y);
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Interfaz");
    glutFullScreen();

    // Registrar las funciones de callback
    interfaz.init();
    glutDisplayFunc(onDraw);
    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouse);
    glutKeyboardFunc(onKeyboard);

    glutMainLoop();
    return 0;
}