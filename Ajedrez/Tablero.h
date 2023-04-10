#ifndef TABLERO_H
#define TABLERO_H

class Casilla;
class Pieza;
class King;

#include "Casilla.h"
#include "Pieza.h"
#include <stdio.h>
#include "header.h"

class Tablero
{
private:
	Casilla *m_casilla[BOARD_SIZE];
	color turn = color::Blanco;
	string	m_initial_board;
public:
	Tablero (string fen = INITIAL_POS);
	~Tablero ();
	void	print();
	string	get_fen();
	Casilla get_cell(int x);
	Casilla get_cell(int x, int y);
	Casilla get_cell(char c, int y);
	Casilla get_cell(Casilla self, int relative_x, int relative_y);
	void	set_possible_moves(Casilla cell);
	void	reset_possible_moves();
	bool	can_Move_To(Casilla dst, Casilla src);
	// bool	is_move_wall(Casilla dst, Casilla src);
	bool	is_empty(Casilla dst);
	// bool	is_enemy_piece(Casilla dst, Pieza);
	void	posible_king(Casilla cell);
	void	posible_queen(Casilla cell);
	void	posible_rook(Casilla cell);
	void	posible_bishop(Casilla cell);
	void	posible_knight(Casilla cell);
	void	posible_pawn(Casilla cell);
	void	printPosibleMoves (Casilla cell);
};

#endif
