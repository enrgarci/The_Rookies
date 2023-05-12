#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include "Interface.h"
#include "Menu.h"
#include "Boton.h"
#include "Window.h"


Window window;
Interface interfaz;
Menu menus;


void onDraw() 
{
	//system("cls");
	std::cout << "Estado: " << menus.getEstado();
	switch (menus.getEstado())
	{
	case (Menu::INICIO_MENU): //1
		menus.drawInicio();
		break;

	case (Menu::DEPASO_MENU):
		menus.drawDepaso();
		break;
	case (Menu::INSTRUCIONES_MENU):
		menus.drawInstrucciones();
		break;
	case (Menu::OPCION_MENU):
		if (menus.getEstadoSkin() == 1) { menus.drawOpcionClassic(); }
		if (menus.getEstadoSkin() == 2) { menus.drawOpcionPvsz(); }
		if (menus.getEstadoSkin() == 3) { menus.drawOpcionSW(); }

		break;

	case (Menu::JUEGO1VS1_MENU)://5
		interfaz.drawBoard(menus.getEstadoSkin());
		interfaz.drawPieces(menus.getEstadoSkin());
		
		interfaz.drawMovement(menus.getEstadoSkin());
		interfaz.reloj();
		break;

	case (Menu::CREDITOS_MENU):
		

		break;
	case (Menu::JUEGO1VSIA_MENU):

		break;
	case (Menu::FINGANADO_MENU):

		break;
	case (Menu::FINPERDIDO_MENU):

		break;
	case (Menu::TABLAS_MENU):

		break;
	case (Menu::EXIT_MENU):
		menus.drawExit();
		break;
	case (Menu::SUBMENU_MENU):
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