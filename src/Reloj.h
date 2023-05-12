#pragma once
#include "Boton.h"
#include "header.h"
#include "ETSIDI.h"
class Partida;

class Reloj
{
private:
		Boton aguja, marco;
	float theta;
	float ClengthANDheight;
	float ClengthMAX;
	float ClengthMIN;
	float Alength;
	float Aheight;
	float Rinc = 2;
	int posx; //1215 o 1215/2
	int posxAguja;

	color c;

public:

	Reloj();
	Reloj(int posx, int posAguja,color colorR) : posx(posx), posxAguja(posxAguja), c(colorR) {};
	void draw(Partida &P);
};

