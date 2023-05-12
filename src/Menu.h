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
	Boton instrucciones, opciones, juego1vs1,
		juego1vsia, creditos, Logo, depaso, exit;
	//Buttons in options
	Boton homefromBoton, classic, pvsz, sw, pk, visualiza;
	//Buttons in submenu
	Boton BotonGuardar, BotonCargar, Boton3min, Boton5min, Boton10min, BotonReanudar, BotonMenuPpal;
	int aumento=1;


public:
	enum ventana {
		INICIO_MENU = 1,       DEPASO_MENU,   INSTRUCIONES_MENU,     OPCION_MENU, 
		JUEGO1VS1_MENU,    JUEGO1VSIA_MENU,   FINGANADO_MENU,    FINPERDIDO_MENU, 
		TABLAS_MENU,         CREDITOS_MENU,   SUBMENU_MENU, EXIT_MENU, MenuInicioPartida
	};//en la ventanaDEPASO estan las instrucciones juego1vs1 juego1vsia y opcion

	//enum skin { normal = 0, classic = 1, pvsz, sw };

	int getEstado() { return Estado; }
	int getEstadoSkin() { return EstadoSkin; }
	int* returnEstado() { return &Estado; }
	void menusIni();
	void drawInicio(void);
	void drawDepaso(void);
	void drawInstrucciones(void);

	void drawOpcionClassic(void);
	void drawOpcionPvsz(void);
	void drawOpcionSW(void);
	void drawSubmenu(void);
	void drawExit(void) { glutDestroyWindow(glutGetWindow()); }
	void drawInicioPartida(void);

	void reshape(int w, int h);
	//void cambioVentana();
	void poligonoVistaImagen(void);
	//void poligonoLogo(void);
	void keyboardVentana(unsigned char key, int x, int y);
	void botonVentana(int button, int state, int x, int y);
};