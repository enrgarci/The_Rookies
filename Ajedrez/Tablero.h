/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-27 22:16:50
 //  Description:
 //
 
#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"
#include "Moves.h"

using std::cout;
using std::endl;
using std::string;

enum Turno {Blanco, Negro};

 class Tablero
{
private:
	Casilla m_casilla[64];
	Casilla	m_last_move[2];				///#TODO
	Casilla	*m_possible_moves;
	Turno	m_mueve;
	string	m_initial_board;
	string	m_game;						///TODO
	bool	m_can_castle = true;		///#TODO
	bool	m_can_en_passant = false;	///#TODO
	int		m_fifty_move_rule = 0;		///#TODO
	int		m_repeat_three = 0;			///#TODO
	friend	class Moves;						///#TODO
public:
	Tablero (string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	void	print();
	string	get_fen();
	Casilla get_cell(int x);
	Casilla get_cell(int x, int y);
	Casilla get_cell(char c, int y);
	Casilla get_cell(Casilla self, int relative_x, int relative_y);
	Casilla *get_possible_moves(Casilla cell);
};

#endif
