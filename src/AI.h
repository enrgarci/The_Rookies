#pragma once
#include "Tablero.h"

class AI
{
private: 
	bool enable = false;
public:
	void randommove(Tablero &T, color col); //the AI makes a move randomly, selecting one of its available pieces only if that piece has moves that it can perform, then moves from its initial square to one selectect from its posible moves at random
	void ON() { enable = true; std::cout << "\n IA ON"; }
	void OFF() { enable = false;  std::cout << "\n IA OFF"; }
};

