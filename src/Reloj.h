#pragma once
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
	//float posxAguja;
	float posy;
	float size, minsize, amplitud;
	float aum;
	color c;
public:
	Reloj();
	Reloj(const float posx, const float posy, const float size, const color colorR) :
		posx(posx), posy(posy), size(size), c(colorR),
		minsize(size), amplitud(size * 0.05), aum(0.1) {};
	void draw(Partida& P);
};