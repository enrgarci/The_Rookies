#include "Menu.h"
#include <iostream>
#include <freeglut.h>
#include <ETSIDI.h>
#include "Boton.h"

void Menu::menusIni()
{
	//inicializa valores 
	fullscreen = true;
	screen_width = glutGet(GLUT_SCREEN_WIDTH);
	screen_height = glutGet(GLUT_SCREEN_HEIGHT);
	coordinate coordenadas;
	coordenadas.x = 0;
	coordenadas.y = 0;
	Estado = 1;//play
	EstadoSkin = 1;//classic
}

void Menu::drawinicio(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 0, g = 200, b = 200;

	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ImagenInicio.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//dibujas boton averiguar como hacer transparente y no repetir imagen
	depaso.Set(buttonsXPosition, 8.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 3.5 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, 250, 250, 250);

	depaso.Draw();

	//glDisable(GL_TEXTURE_2D);
	glDisable(GL_ALPHA_TEST); //transparencia
	//glDisable(GL_BLEND); // mezcla de color
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/ImagenInicio.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
}

void Menu::drawdepaso(void)
{
	//Common parameters of the buttons
	int buttonsHeightMenu = 2.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;

	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/depaso.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo
	if (EstadoSkin == 1)

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


	glDisable(GL_TEXTURE_2D);
	//glDisable(GL_ALPHA_TEST);
	//glDisable(GL_BLEND);


	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/depaso.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo
}

void Menu::drawinstrucciones(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 2.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 8 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Intruciones.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);

	depaso.Set(buttonsXPosition, 6 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 4 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	depaso.Draw();

	//fin imagen fondo
}
void Menu::drawopciones(void)
{
	//Common parameters of the buttons
	int buttonsHeightMenu = 4 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;


	//dibujando los botones
	classic.Set(buttonsXPosition, 13 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 8 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	buttonsXPosition = 7 * glutGet(GLUT_WINDOW_WIDTH) / 20;// cambiamos posicion x
	pvsz.Set(buttonsXPosition, 7.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	sw.Set(buttonsXPosition, 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	classic.Draw();
	pvsz.Draw();
	sw.Draw();
	glDisable(GL_TEXTURE_2D);


	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesNormal.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo

	int h = glutGet(GLUT_WINDOW_HEIGHT), w = glutGet(GLUT_WINDOW_WIDTH);
	buttonsHeightMenu = 5 * h / 20;
	int buttonsWidth = 10 * h / 20;
	buttonsXPosition = 8 * w / 20;
	//Main menu
	//Seting position, size, and color
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

//cosas de imagen
void Menu::reshape(int w, int h)
{

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

void Menu::keyboardVentana(unsigned char key, int x, int y)
{
	const char KEY = '1';
	if (key == KEY) { Estado = 1; std::cout << "va1"; }
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
	//Change the current window to the one selected by a button

	//Main menu
	if (Estado == 1) {
		if (depaso.isInside(button, state, x, y)) Estado = 2;
	}
	//depaso
	if (Estado == 2) {
		if (juego1vs1.isInside(button, state, x, y)) Estado = 5;
		if (juego1vsia.isInside(button, state, x, y)) Estado = 6;
		if (instrucciones.isInside(button, state, x, y)) Estado = 3;
		if (opciones.isInside(button, state, x, y)) Estado = 4;
	}
	//instrucciones
	if (Estado == 3) {
		if (depaso.isInside(button, state, x, y)) Estado = 2;
	}
	//Options
	if (Estado == 4)
	{
		enum skin { classic = 1, pvsz, sw };

		if (Menu::classic.isInside(button, state, x, y)) {
			EstadoSkin = classic;
			drawopcionclassic();
		}
		else if (Menu::pvsz.isInside(button, state, x, y)) {
			EstadoSkin = pvsz;
			drawopcionpvsz();
		}
		else if (Menu::sw.isInside(button, state, x, y)) {
			EstadoSkin = sw;
			drawopcionsw();
		}

		if (homefromBoton.isInside(button, state, x, y)) Estado = 2;
	}
	//1vs1
	//if (Estado == 5) {
	//	if (depaso.isInside(button, state, x, y)) Estado = 2;
	//}

}
void Menu::drawopcionclassic(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 4 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;


	//dibujando los botones
	classic.Set(buttonsXPosition, 13 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 8 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	buttonsXPosition = 7 * glutGet(GLUT_WINDOW_WIDTH) / 20;// cambiamos posicion x
	pvsz.Set(buttonsXPosition, 7.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	sw.Set(buttonsXPosition, 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	classic.Draw();
	pvsz.Draw();
	sw.Draw();
	glDisable(GL_TEXTURE_2D);


	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesClassic.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo

	int h = glutGet(GLUT_WINDOW_HEIGHT), w = glutGet(GLUT_WINDOW_WIDTH);
	buttonsHeightMenu = 5 * h / 20;
	int buttonsWidth = 10 * h / 20;
	buttonsXPosition = 8 * w / 20;
	//Main menu
	//Seting position, size, and color
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
void Menu::drawopcionpvsz(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 4 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;


	//dibujando los botones
	classic.Set(buttonsXPosition, 13 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 8 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	buttonsXPosition = 7 * glutGet(GLUT_WINDOW_WIDTH) / 20;// cambiamos posicion x
	pvsz.Set(buttonsXPosition, 7.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	sw.Set(buttonsXPosition, 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	classic.Draw();
	pvsz.Draw();
	sw.Draw();
	glDisable(GL_TEXTURE_2D);


	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesPVSZ.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo
	// 
	// 
	int h = glutGet(GLUT_WINDOW_HEIGHT), w = glutGet(GLUT_WINDOW_WIDTH);
	buttonsHeightMenu = 5 * h / 20;
	int buttonsWidth = 10 * h / 20;
	buttonsXPosition = 8 * w / 20;
	//Main menu
	//Seting position, size, and color
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
void Menu::drawopcionsw(void) {
	//Common parameters of the buttons
	int buttonsHeightMenu = 4 * glutGet(GLUT_WINDOW_HEIGHT) / 20;
	int buttonsXPosition = 6 * glutGet(GLUT_WINDOW_WIDTH) / 20;
	int r = 250, g = 0, b = 250;


	//dibujando los botones
	classic.Set(buttonsXPosition, 13 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 8 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	buttonsXPosition = 7 * glutGet(GLUT_WINDOW_WIDTH) / 20;// cambiamos posicion x
	pvsz.Set(buttonsXPosition, 7.5 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	sw.Set(buttonsXPosition, 2 * glutGet(GLUT_WINDOW_HEIGHT) / 20, 6 * glutGet(GLUT_WINDOW_WIDTH) / 20, buttonsHeightMenu, r, g, b);
	classic.Draw();
	pvsz.Draw();
	sw.Draw();
	glDisable(GL_TEXTURE_2D);


	//Background picture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/Opciones/OpcionesSW.png").id);
	poligonoVistaImagen();
	glDisable(GL_TEXTURE_2D);
	//fin imagen fondo
	// 
	// 
	int h = glutGet(GLUT_WINDOW_HEIGHT), w = glutGet(GLUT_WINDOW_WIDTH);
	buttonsHeightMenu = 5 * h / 20;
	int buttonsWidth = 10 * h / 20;
	buttonsXPosition = 8 * w / 20;
	//Main menu
	//Seting position, size, and color
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