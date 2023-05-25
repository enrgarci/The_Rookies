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
	float posx; 
	float posy;
	float size;
	color c;

public:

	Reloj();
	Reloj(const float posx,const float posy,const float size,const color colorR) : posx(posx), posy(posy), size(size), c(colorR) {};
	void draw(Partida &P);
};

