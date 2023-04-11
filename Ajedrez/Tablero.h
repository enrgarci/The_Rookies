#ifndef TABLERO_H
#define TABLERO_H

class Casilla;
class Pieza;

#include <stdio.h>
#include "header.h"

class Tablero
{
private:
	Casilla *m_casilla[BOARD_SIZE];
	color turn = color::Blanco;
	string	m_initial_board;
	bool	m_w_castle_rights = true;
	bool	m_b_castle_rights = true;
public:
	int	move_count = 0;
	Tablero (string fen = INITIAL_POS);
	~Tablero ();
	void	print();
	string	get_fen();
	Casilla *get_cell(int x);
	Casilla *get_cell(int x, int y);
	Casilla *get_cell(char c, int y);
	Casilla *get_cell(Casilla self, int relative_x, int relative_y);
	void	set_possible_moves(Casilla cell);
	void	reset_possible_moves();
	bool	can_Move_To(Casilla dst, Casilla src);
	bool	is_move_wall(Casilla dst, Casilla src);
	bool	is_empty(Casilla dst);
	bool	is_enemy_piece(Casilla dst, color myColor);
	void	printPosibleMoves (Casilla cell);
	bool	can_castle(color c);
	void	set_castle(bool state, color c);
	void	set_castle();
};

#endif
