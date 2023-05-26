#include "Menu.h"
#include <iostream>
#include <freeglut.h>
#include <ETSIDI.h>
#include "Boton.h"
#include "header.h"
#include <cstring>
#include <SoundController.h>

SoundController So;

void Menu::Draw()
{
	system("cls");
	std::cout << "Estado: " << getEstado();
	switch (Estado)
	{
	case (Menu::INICIO_MENU):
		drawInicio();
		break;

	case (Menu::DEPASO_MENU):
		drawDepaso();
		break;
	case (Menu::INSTRUCIONES_MENU):
		drawInstrucciones();
		break;
	case (Menu::OPCION_MENU):
		drawOpcion();
		break;
	case (Menu::JUEGO1VS1_MENU):
		interfaz.drawBoard(getEstadoSkin());
		interfaz.drawPieces(getEstadoSkin());
		interfaz.drawMovement(getEstadoSkin());
		interfaz.enableIA(false);
		estdoPartidaDraw();
		break;
	case (Menu::CREDITOS_MENU):
		break;
	case (Menu::JUEGO1VSIA_MENU):
		interfaz.drawBoard(getEstadoSkin());
		interfaz.drawPieces(getEstadoSkin());
		interfaz.drawMovement(getEstadoSkin());
		interfaz.enableIA(true);
		estdoPartidaDraw();
		break;
	case (Menu::FINBLANCAS_MENU):
		drawFinBlancas();
		break;
	case (Menu::FINNEGRAS_MENU):
		drawFinNegras();
		break;
	case (Menu::TABLAS_MENU):
		drawTablas();
		break;
	case (Menu::EXIT_MENU):
		drawExit();
		break;
	case (Menu::SUBMENU_MENU):
		drawSubmenu();

		break;
	default: std::cout << "Ha fallado el source ventana";
		break;
	}

	//glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
	glutSwapBuffers();
}


void Menu::menusIni(Interface inter)
{
	//inicializa valores 
	interfaz = inter;
	interfaz.init();
	fullscreen = true;
	screen_width = glutGet(GLUT_SCREEN_WIDTH);
	screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	coordinate coordenadas;
	coordenadas.x = 0;
	coordenadas.y = 0;
	Estado = 1;//play
	EstadoSkin = 1;//classic
	imagenInstruccion = 1;
	tiempo = 180; //3min default
	aum3min = 1.2;
	aum5min = 1.0;
	aum10min = 1.0;
}

void Menu::drawInicio(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int const r = 0, g = 200, b = 200;

	//boton
	depaso.Set(buttonsXPosition, 8.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 3.5 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	depaso.Draw();

	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST); //transparencia
	//glDisable(GL_BLEND); // mezcla de color
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ImagenInicio.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
}

void Menu::drawDepaso(void)
{
	//Common parameters of the buttons
	int buttonsHeightMenu = 2.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int const r = 250, g = 0, b = 250;

	juego1vs1.Set(buttonsXPosition, 16 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 4 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	juego1vs1.Draw();
	juego1vsia.Set(buttonsXPosition, 12.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 4 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	juego1vsia.Draw();
	buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	instrucciones.Set(buttonsXPosition, 9 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 7 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	instrucciones.Draw();
	buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	opciones.Set(buttonsXPosition, 6 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 4 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	opciones.Draw();
	exit.Set(buttonsXPosition, 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 4 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	exit.Draw();

	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/depaso.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo
}

void Menu::drawInstrucciones(void) {

	//Common parameters of the buttons
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	float w = glutGet(GLUT_WINDOW_WIDTH);
	int const r = 250, g = 250, b = 250;

	BotonSiguiente.Set(w * 55 / 64, h * 54 / 64, w * 5 / 64, h * 5 / 64, r, g, b);
	BotonAnterior.Set(w * 55 / 64, h * 49 / 64, w * 5 / 64, h * 5 / 64, r, g, b);

	glEnable(GL_TEXTURE_2D);
	if (imagenInstruccion == 1)
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Instrucciones/Instruccion1.png").id);
	if (imagenInstruccion == 2)
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Instrucciones/Instruccion2.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Left-Arrow.png").id);
	BotonAnterior.Draw();

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ButtonsInterface/Right-Arrow.png").id);
	BotonSiguiente.Draw();//1 adelante


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);


	botonHomeDraw();

}
void Menu::drawFinBlancas(void) {

	glEnable(GL_TEXTURE_2D);
	if (EstadoSkin == 1) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_clasico/BlancoWin.png").id);
	}
	else if (EstadoSkin == 2) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_pvsz/BlancoWin.png").id);
	}
	else if (EstadoSkin == 3) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_sw/BlancoWin.png").id);
	}

	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	botonHomeDraw();
}
void Menu::drawFinNegras(void) {

	glEnable(GL_TEXTURE_2D);
	if (EstadoSkin == 1) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_clasico/NegroWin.png").id);
	}
	else if (EstadoSkin == 2) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_pvsz/NegroWin.png").id);
	}
	else if (EstadoSkin == 3) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_sw/NegroWin.png").id);
	}
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	botonHomeDraw();
}
void Menu::drawTablas(void) {

	glEnable(GL_TEXTURE_2D);
	if (EstadoSkin == 1) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_clasico/Tablas.png").id);
	}
	else if (EstadoSkin == 2) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_pvsz/Tablas.png").id);
	}
	else if (EstadoSkin == 3) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Menu_sw/Tablas.png").id);
	}
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	botonHomeDraw();
}

void Menu::poligonoVistaImagen(void) {
	float x = (float)screen_width / screen_height;
	float y = (float)screen_height / screen_height;
	//coordenas de un plano con la imagen+pantalla
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(1, 1);     glVertex2f(x, 0);
	glTexCoord2d(0, 1);     glVertex2f(0, 0);
	glTexCoord2d(0, 0);     glVertex2f(0, y);
	glTexCoord2d(1, 0);     glVertex2f(x, y);
	glEnd();
}

void Menu::keyboardVentana(unsigned char key, int x, int y)
{
	if (key == '1') { Estado = 1; std::cout << "va1"; }
	if (key == '2') { Estado = 2; std::cout << "va2"; }
	if (key == '3') { Estado = 3; std::cout << "va3"; }
	if (key == '4') { Estado = 4; std::cout << "va4"; }
	if (key == '5') { Estado = 5; std::cout << "va5"; }
	if (key == '6') { Estado = 6; std::cout << "va6"; }
	if (key == '7') { Estado = 7; std::cout << "va7"; }
	if (key == '8') { Estado = 8; std::cout << "va8"; }
}

void Menu::botonVentana(int button, int state, int x, int y)
{
	//Tablero tablero;
	//Change the current window to the one selected by a button
	system("cls");
	//Main menu
	if (Estado == INICIO_MENU) {
		if (depaso.isInside(button, state, x, y)) Estado = DEPASO_MENU;
	}
	//depaso
	if (Estado == DEPASO_MENU) {
		if (juego1vs1.isInside(button, state, x, y)) Estado = JUEGO1VS1_MENU;
		if (juego1vsia.isInside(button, state, x, y)) Estado = JUEGO1VSIA_MENU;
		if (instrucciones.isInside(button, state, x, y)) Estado = INSTRUCIONES_MENU;
		if (opciones.isInside(button, state, x, y)) Estado = OPCION_MENU;
		if (exit.isInside(button, state, x, y)) Estado = EXIT_MENU;
		imagenInstruccion = 1;
	}
	//instrucciones
	if (Estado == INSTRUCIONES_MENU) {
		if (homefromBoton.isInside(button, state, x, y)) Estado = DEPASO_MENU;
		if (BotonSiguiente.isInside(button, state, x, y) && imagenInstruccion == 1) imagenInstruccion = 2;
		if (BotonAnterior.isInside(button, state, x, y) && imagenInstruccion == 2) imagenInstruccion = 1;
	}
	//Options
	if (Estado == OPCION_MENU)
	{
		enum skin { classic = 1, pvsz, sw };

		if (Menu::classic.isInside(button, state, x, y)) {
			EstadoSkin = classic;
			drawOpcion();
		}
		else if (Menu::pvsz.isInside(button, state, x, y)) {
			EstadoSkin = pvsz;
			drawOpcion();
		}
		else if (Menu::sw.isInside(button, state, x, y)) {
			EstadoSkin = sw;

			drawOpcion();
		}
		//Time buttons
		if (Boton3min.isInside(button, state, x, y))
		{
			tiempo = 180;
			aum3min = 1.2;
			aum5min = 1.0;
			aum10min = 1.0;
		}
		if (Boton5min.isInside(button, state, x, y))
		{
			tiempo = 300;
			tiempo = 180;
			aum3min = 1.0;
			aum5min = 1.2;
			aum10min = 1.0;
		}
		if (Boton10min.isInside(button, state, x, y))
		{
			tiempo = 600;
			tiempo = 180;
			aum3min = 1.0;
			aum5min = 1.0;
			aum10min = 1.2;

		}

		if (homefromBoton.isInside(button, state, x, y)) Estado = DEPASO_MENU;
	}

	if (Estado == SUBMENU_MENU)
	{
		//std::cout << "Probando"<< BotonGuardar.isInside(button, state, x, y);
		if (BotonGuardar.isInside(button, state, x, y))
		{

			std::cout << "GUARDADO";
		}
		if (BotonExit.isInside(button, state, x, y))
		{
			Estado = EXIT_MENU;
			std::cout << "CARGADO";
		}

		if (BotonReanudar.isInside(button, state, x, y))
		{
			Estado = 5;
		}
		if (BotonMenuPpal.isInside(button, state, x, y))
		{
			Estado = DEPASO_MENU;
		}
	}
	if (Estado == FINBLANCAS_MENU || Estado == FINNEGRAS_MENU || Estado == TABLAS_MENU) {

		if (homefromBoton.isInside(button, state, x, y)) Estado = DEPASO_MENU;
	}
	if (Estado == EXIT_MENU)
	{
		if (exit.isInside(button, state, x, y)) Estado = EXIT_MENU;
	}
}

void Menu::botonHomeDraw() {
	int buttonsHeightMenu = 4 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int const r = 250, g = 0, b = 250;
	int h = glutGet(GLUT_WINDOW_HEIGHT), w = glutGet(GLUT_WINDOW_WIDTH);
	buttonsHeightMenu = 5 * h / 20;
	int buttonsWidth = 10 * h / 20;
	buttonsXPosition = 8 * w / 20;
	//Main menu
	//Seting position, size, and color
	homefromBoton.Set(0.9 * w / 20, 16.8 * h / 20, buttonsHeightMenu / 2.5, buttonsHeightMenu / 2.5, 160, 200, 100);
	homefromBoton.Set(0.9 * w / 20, 16.8 * h / 20, buttonsHeightMenu / 2.5, buttonsHeightMenu / 2.5, 160, 200, 100);
	homefromBoton.Draw();
	//Drawing
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Home.png").id);
	homefromBoton.Set(1 * w / 20, 17 * h / 20, buttonsHeightMenu / 3, buttonsHeightMenu / 3, 100, 250, 100);
	homefromBoton.Draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
	//End of Main menu button
}

void Menu::drawOpcion(void) {
	//Common parameters of the buttons
	float w = glutGet(GLUT_WINDOW_WIDTH);
	float h = glutGet(GLUT_WINDOW_HEIGHT);
	float buttonsHeightMenu = 27 * h / 100;
	float timebuttonsHeight = 10 * h / 100;
	float buttonsXPosition = 32.5 * w / 100;
	float timebuttonsXPosition = w * 3 / 64;
	float buttonslength = 50 * w / 100;
	float timebuttonslength = 20 * w / 100;
	float const r = 250, g = 0, b = 250;
	//Sets properties of each button
	classic.Set(buttonsXPosition, 12 * h / 20, buttonslength, buttonsHeightMenu, 250, 0, 0);//, r, g, b);
	pvsz.Set(buttonsXPosition, 6.5 * h / 20, buttonslength, buttonsHeightMenu, 0, 250, 0);
	sw.Set(buttonsXPosition, 1 * h / 20, buttonslength, buttonsHeightMenu, 0, 0, 250);
	Boton3min.Set(timebuttonsXPosition, h * 28 / 64, timebuttonslength * aum3min, timebuttonsHeight * aum3min, 250, 250, 250);
	Boton5min.Set(timebuttonsXPosition, h * 18 / 64, timebuttonslength * aum5min, timebuttonsHeight * aum5min, 250, 250, 250);
	Boton10min.Set(timebuttonsXPosition, h * 8 / 64, timebuttonslength * aum10min, timebuttonsHeight * aum10min, 250, 250, 250);

	//Draws each button


	glDisable(GL_TEXTURE_2D);
	//Background picture
	glEnable(GL_TEXTURE_2D);
	if (EstadoSkin == 1) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesClassic.png").id);
	}
	else if (EstadoSkin == 2) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesPVSZ.png").id);
	}
	else if (EstadoSkin == 3) {
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesSW.png").id);
	}
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo

	//Time button

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/3min.png").id);
	Boton3min.Draw();
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/5min.png").id);
	Boton5min.Draw();
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/10min.png").id);
	Boton10min.Draw();
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);

	//DIBUJAR BOTON LLAMANDO A SU FUNCION
	botonHomeDraw();

}

void Menu::drawSubmenu(void)
{
	//Boton BotonGuardar, BotonCargar, Boton3min, Boton5min, Boton10min;
	float w = glutGet(GLUT_WINDOW_WIDTH), h = glutGet(GLUT_WINDOW_HEIGHT);
	glClearColor(0.03f, 0.52f, 0.11f, 0.5f); // background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SET POSITION AND COLOR
	BotonReanudar.Set(6 * w / 16, 11 * h / 16, 4 * w / 16, 2 * h / 16, 200, 200, 200);
	BotonMenuPpal.Set(5.5 * w / 16, 8 * h / 16, 5 * w / 16, 2 * h / 16, 200, 200, 200);
	BotonGuardar.Set(4 * w / 16, 5 * h / 16, 3.25 * w / 16, 2 * h / 16, 200, 200, 200);
	BotonExit.Set(9 * w / 16, 5 * h / 16, 3 * w / 16, 2 * h / 16, 200, 200, 200);



	//Drawing
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.5f);

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Submenu/Reanudar.png").id);
	BotonReanudar.Draw();

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Submenu/MenuPpal.png").id);
	BotonMenuPpal.Draw();

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Submenu/GUARDAR.png").id);
	BotonGuardar.Draw();

	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Submenu/exit.png").id);
	BotonExit.Draw();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_BLEND);
}

void Menu::ratonInterfaz(int button, int state, int x, int y) {
	interfaz.mouseBoard(button, state, x, y, *returnEstado());
}
void Menu::keyboardFullscreenMenu(unsigned char key, int x, int y) {
	interfaz.keyboardFullscreen(key, x, y);
}

void Menu::estdoPartidaDraw(void) {
	if (Estado != FINBLANCAS_MENU) {
		if (Estado != FINNEGRAS_MENU) {
			if (Estado != TABLAS_MENU) {
				if (interfaz.EstadoPartida == Interface::GANADOBLANCAS) Estado = FINBLANCAS_MENU;
				else if (interfaz.EstadoPartida == Interface::GANADONEGRAS) Estado = FINNEGRAS_MENU;
				else if (interfaz.EstadoPartida == Interface::TABLAS) Estado = TABLAS_MENU;
			}
		}
	}
}