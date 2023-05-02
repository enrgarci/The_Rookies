#ifndef PARTIDA_H
#define PARTIDA_H

#include "Tablero.h"
#include "header.h"
#include <fstream>


class Partida
{
private:
	string	m_w_player;
	string	m_b_player;
	int current_pos = 0;
public:
	vector<FEN> positions;
	Tablero *T;
	Partida(string w_player,
			string b_player,
			string init_pos = INITIAL_POS);
	Partida(string w_player,
			string b_player,
			vector<FEN> &game): m_w_player(w_player), 
								m_b_player(b_player), positions(game),
								T(new Tablero((*this), game.at(0))){};
	Partida(std::fstream &file);
	~Partida();
	Tablero	&getBoard();
	string	getPlayer(int col=0);
	void	play_back();
	void	play_forward();
	void	play_first();
	void	play_last();
	void	add_pos();
	void	undoMove();
	int		getCurrentPos();
	int		perf(Partida &p, int depth);
	void	save(string directory = "./",string name = "myGame.txt");
};

inline int Partida::getCurrentPos(){return positions.size() - 1;};
#endif
