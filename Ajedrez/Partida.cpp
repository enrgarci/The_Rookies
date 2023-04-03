#include "Partida.h"

Partida::Partida(string w_player, string b_player, string init_pos)
{
	board = Tablero(init_pos);
	m_w_player = w_player;
	m_b_player = b_player;
}

Tablero Partida::getBoard()
{
	return board;
}

string Partida::getPlayer(int col)
{
	if (col == 2) return(m_b_player);
	if (col == 1) return(m_w_player);
	return m_w_player + "/" + m_b_player;
}