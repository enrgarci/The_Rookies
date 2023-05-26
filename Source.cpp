#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include "Interface.h"
#include "Menu.h"
#include "Window.h"

//Interface interfaz;
Menu menus;


void onDraw() {
    menus.Draw();
}
void onReshape(int w, int h) 
{
    Window window;
	window.reshape(w, h);
}

void onMouse(int button, int state, int x, int y) 
{
	int estado;
	
    //interfaz.mouseBoard(button, state, x, y, *menus.returnEstado());
    menus.ratonInterfaz(button, state, x, y);
	menus.botonVentana(button, state, x, y);

}

void onKeyboard(unsigned char key, int x, int y) 
{
	menus.keyboardVentana(key, x, y);
    menus.keyboardFullscreenMenu(key, x, y);
}

int main(int argc, char** argv) 
{
	//Menu menus;
    Interface interfaz;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Interfaz");
    glutFullScreen();

    // Registrar las funciones de callback
    interfaz.init();
	menus.menusIni(interfaz);
    glutDisplayFunc(onDraw);
    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouse);
    glutKeyboardFunc(onKeyboard);
 
    glutMainLoop();
    return 0;
}