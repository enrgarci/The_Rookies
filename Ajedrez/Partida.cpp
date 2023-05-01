#include "Partida.h"
#include "Tablero.h"

Partida::Partida(string w_player, string b_player, string init_pos)
{
	T = new Tablero(*this, init_pos);
	m_w_player = w_player;
	m_b_player = b_player;
}

Partida::~Partida()
{
}

Tablero &Partida::getBoard()
{
	return *T;
}

string Partida::getPlayer(int col)
{
	if (col == 2) return(m_b_player);
	if (col == 1) return(m_w_player);
	return m_w_player + "/" + m_b_player;
}

void Partida::play_back()
{
	if(current_pos >= 1) 
	{
		current_pos--;
		T = new Tablero(*this, positions.at(current_pos));
	}
}

void Partida::play_forward()
{
	if(current_pos < positions.size() - 1) 
	{
		current_pos++;
		T = new Tablero(*this,positions.at(current_pos));
	}
}

void Partida::play_last()
{
	current_pos = positions.size() - 1;
	T = new Tablero(*this,positions.at(current_pos));
}
void Partida::play_first()
{
	current_pos = 0;
	T = new Tablero(*this,positions.at(current_pos));
}

void Partida::add_pos()
{
	if (current_pos == positions.size() - 1)
		positions.push_back((*T).get_fen());
}
