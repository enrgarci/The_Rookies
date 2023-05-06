#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include "Interface.h"
#include "Menu.h"
#include "Boton.h"
#include "Window.h"
#include <cstdlib>

Window window;
Interface interfaz;
Menu menus;


void onDraw() 
{
	//system("cls");
	std::cout << "Estado: " << menus.getEstado();
	switch (menus.getEstado())
	{
	case (Menu::INICIO): //1
		menus.drawinicio();
		break;

	case (Menu::DEPASO):
		menus.drawdepaso();
		break;
	case (Menu::INSTRUCIONES):
		menus.drawinstrucciones();
		break;
	case (Menu::OPCION):
		menus.drawopciones();
		break;

	case (Menu::JUEGO1VS1)://5
		interfaz.drawBoard(menus.getEstadoSkin());
		interfaz.drawPieces(menus.getEstadoSkin());
		interfaz.drawMovement(menus.getEstadoSkin());


		break;
	case (Menu::JUEGO1VSIA):

		break;
	case (Menu::FINGANADO):

		break;
	case (Menu::FINPERDIDO):

		break;
	case (Menu::TABLAS):

		break;
	case (Menu::CREDITOS):


		break;
	case (Menu::SUBMENU):
		menus.drawSubmenu();

		break;
	default: std::cout << "Ha fallado el source ventana";
		break;
	}


	//glClear(GL_COLOR_BUFFER_BIT);

    glutSwapBuffers();
}

void onReshape(int w, int h) 
{
    
	window.reshape(w, h);
}

void onMouse(int button, int state, int x, int y) 
{
	int estado;
	
    interfaz.mouseBoard(button, state, x, y, *menus.returnEstado());

	menus.botonVentana(button, state, x, y);

}

void onKeyboard(unsigned char key, int x, int y) 
{
    interfaz.keyboardFullscreen(key, x, y);
	menus.keyboardVentana(key, x, y);
}

int main(int argc, char** argv) 
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));
    glutCreateWindow("Interfaz");
    glutFullScreen();

    // Registrar las funciones de callback
    interfaz.init();
	menus.menusIni();
    glutDisplayFunc(onDraw);
    glutReshapeFunc(onReshape);
    glutMouseFunc(onMouse);
    glutKeyboardFunc(onKeyboard);
 
    glutMainLoop();
    return 0;
}