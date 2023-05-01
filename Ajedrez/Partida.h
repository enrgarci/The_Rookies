#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include "header.h"

const string DEF_W_PLAYER = "JugBlanco";
const string DEF_B_PLAYER = "JugNegro";

class Partida
{
private:
	string	m_w_player;
	string	m_b_player;
	vector<FEN> positions;
	int current_pos = 0;
public:
	Tablero *T;
	Partida(string w_player = DEF_W_PLAYER,
			string b_player = DEF_B_PLAYER,
			string init_pos = INITIAL_POS);
	Partida(string w_player,
			string b_player,
			vector<FEN> &game): m_w_player(w_player), 
								m_b_player(b_player), positions(game),
								T(new Tablero((*this), game.at(0))){};
	~Partida();
	Tablero	&getBoard();
	string	getPlayer(int col=0);
	void	play_back();
	void	play_forward();
	void	play_first();
	void	play_last();
	void	add_pos();
	int		getCurrentPos();
};

inline int Partida::getCurrentPos(){return positions.size() - 1;};
#endif
