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
	vector<int> m_w_pieces;
	vector<int> m_b_pieces;
public:
	int	move_count = 0;
	Tablero (string fen = INITIAL_POS);
	~Tablero ();
	void	print();
	void	print_all_moves();
	int		count_possible_moves();
	string	get_fen();
	Casilla &get_cell(const int x);
	Casilla &get_cell(const int x, const int y);
	Casilla &get_cell(const char c, const int y);
	Casilla &get_cell(Casilla &self, const int relative_x, const int relative_y);
	void	set_possible_moves(Casilla &cell);
	void	reset_possible_moves();
	bool	can_Move_To(Casilla &dst, Casilla &src);
	bool	is_move_wall(Casilla &dst, Casilla &src);
	bool	is_empty(Casilla &dst);
	bool	is_enemy_piece(Casilla &dst, color myColor);
	void	printPosibleMoves (Casilla &cell);
	bool	can_castle(color c);
	void	set_castle(bool state, color c);
	void	set_castle();
	void	do_move(int from, int to);
	Casilla &operator[](int c);
	color	get_turn(){return turn;};
	vector<int> &get_Color_Pieces(color c); 
};

/// @brief Access a cell of the board
/// @param c the 0-63 cell to access
/// @return The c cell of board, first cell if c not in [0 - 63]
inline Casilla &Tablero::operator[](const int c)
{ if (c >= 0 && c < 64) return *m_casilla[c]; return *m_casilla[0];}

inline vector<int> &Tablero::get_Color_Pieces(color c)
{
	return c == Blanco ? m_w_pieces : m_b_pieces;
}

#endif
