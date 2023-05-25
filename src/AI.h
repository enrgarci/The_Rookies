#pragma once
#include "Tablero.h"

class AI
{
public:
	int randommove(Tablero &T, color col); //the AI makes a move randomly, selecting one of its available pieces only if that piece has moves that it can perform, then moves from its initial square to one selectect from its posible moves at random
};
