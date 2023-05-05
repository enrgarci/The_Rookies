#pragma once
#include "Boton.h"
class Menu
{
private:
	struct coordinate {
		float x, y;
	};
	int screen_width;
	int screen_height;
	bool fullscreen;
	int Estado;
	int EstadoSkin;

	//Buttons in main menu
	Boton instrucciones, opciones, juego1vs1, juego1vsia, creditos, Logo, depaso, exit;
	//Buttons in options
	Boton homefromBoton, classic, pvsz, sw, pk, visualiza;


public:
	enum ventana {
		INICIO = 1, DEPASO, INSTRUCIONES, OPCION,
		JUEGO1VS1, JUEGO1VSIA, FINGANADO, FINPERDIDO, TABLAS, CREDITOS
	};//en la ventanaDEPASO estan las instrucciones juego1vs1 juego1vsia y opcion

	//enum skin { normal = 0, classic = 1, pvsz, sw };

	int getEstado() { return Estado; }
	void menusIni();
	void drawinicio(void);
	void drawdepaso(void);
	void drawinstrucciones(void);
	void drawopciones(void);
	void drawopcionclassic(void);
	void drawopcionpvsz(void);
	void drawopcionsw(void);
	void reshape(int w, int h);
	//void cambioVentana();
	void poligonoVistaImagen(void);
	//void poligonoLogo(void);
	void keyboardVentana(unsigned char key, int x, int y);
	void botonVentana(int button, int state, int x, int y);
	int getEstadoSkin() { return EstadoSkin; }

};

