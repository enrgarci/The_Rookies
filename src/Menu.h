#pragma once
#include "Boton.h"
#include "Interface.h"
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
	Interface interfaz;

	//Buttons in main menu
	Boton instrucciones, opciones, juego1vs1,
		juego1vsia, creditos, Logo, depaso, exit;
	//Buttons in options
	Boton homefromBoton, classic, pvsz, sw, pk, visualiza;
	//Buttons in submenu
	Boton BotonGuardar, BotonCargar, Boton3min, Boton5min, Boton10min, BotonReanudar, BotonMenuPpal;
	int aumento=1;
	//Buttons in instrucciones
	Boton BotonAnterior, BotonSiguiente;
	int imagenInstruccion;

public:
	enum ventana {
		INICIO_MENU = 1,       DEPASO_MENU,   INSTRUCIONES_MENU,     OPCION_MENU, 
		JUEGO1VS1_MENU,    JUEGO1VSIA_MENU,   FINBLANCAS_MENU,    FINNEGRAS_MENU, 
		TABLAS_MENU,         CREDITOS_MENU,   SUBMENU_MENU, EXIT_MENU
	};//en la ventanaDEPASO estan las instrucciones juego1vs1 juego1vsia y opcion


	
	int getEstado() { return Estado; }
	int getEstadoSkin() { return EstadoSkin; }
	int* returnEstado() { return &Estado; }
	void menusIni(Interface interfaz);
	void drawInicio(void);
	void drawDepaso(void);
	void drawInstrucciones(void);
	void drawFinBlancas(void);
	void drawFinNegras(void);
	void drawTablas(void);
	void botonHomeDraw(void);
	void estdoPartidaDraw();
	void keyboardFullscreenMenu(unsigned char key, int x, int y);
	//cosas interfaz
	void ratonInterfaz(int button, int state, int x, int y);
	//fin

	void drawOpcion(void);
	void drawSubmenu(void);
	void drawExit(void) { glutDestroyWindow(glutGetWindow()); }
	void poligonoVistaImagen(void);
	void keyboardVentana(unsigned char key, int x, int y);
	void botonVentana(int button, int state, int x, int y);
	void Draw();
	

	
};
