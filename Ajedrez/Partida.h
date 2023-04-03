#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"

const string DEF_W_PLAYER = "JugBlanco";
const string DEF_B_PLAYER = "JugNegro";

class Partida
{
private:
	string	m_w_player;
	string	m_b_player;
public:
	Tablero board;
	Partida(string w_player = DEF_W_PLAYER,
			string b_player = DEF_B_PLAYER,
			string init_pos = INITIAL_POS);

	Tablero	getBoard();
	string	getPlayer(int col=0);
};

#endif
