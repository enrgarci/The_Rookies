#ifndef TABLERO_H
#define TABLERO_H

//Forward declaration of pieces
class Casilla;
class Pieza;
class King;
class Queen;
class Rook;
class Bishop;
class Knight;
class Pawn;
class Empty;
class Partida;
#include <stdio.h>
#include "header.h"
class Tablero
{
friend class Casilla;
private:
	Partida *m_parent_game;
	Casilla *m_casilla[BOARD_SIZE];
	color turn = color::Blanco;
	bool	m_w_castle_rights[2] = {false, false};
	bool	m_b_castle_rights[2] = {false, false};
	vector<int> m_w_pieces;
	vector<int> m_b_pieces;
	int m_fifty_move_rule = 0;
	bool m_threefold = 0;
	int m_event = None;

	// As the pieces classes only manage the movements, there is
	//no point in having an instance of them per cell, as the parameters needed
	// are passed, instead we have one of a type per board and all the cells of the same type
	// call those, helps less memory management when making moves.
	King	*m_king;
	Queen	*m_queen;
	Rook	*m_rook;
	Knight	*m_knight;
	Bishop	*m_bishop;
	Pawn	*m_pawn;
	Empty	*m_empty;
	//pieza a coronar por defecto Dama
	Pieza *m_coronacion;
	figura	m_promocion = Reina;

public:
	int	move_count = 0;
	Tablero (Partida &p, string fen = INITIAL_POS);
	~Tablero ();
	void	print();
	void	print_checks(color c);
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
	void	printPosibleMoves (int &&cell);
	int		can_castle(color c);
	int		do_move(int from, int to);
	Empty	&get_empty_cell();
	Casilla &operator[](int c);
	color	get_turn(){return turn;};
	bool	hasMoves(color c);
	int		getEvent();
	void	setCoronación(figura f=Reina);
	bool	isThreeFold();
};

/// @brief Access a cell of the board
/// @param c the 0-63 cell to access
/// @return The c cell of board, first cell if c not in [0 - 63]
inline Casilla &Tablero::operator[](const int c)
{ if (c >= 0 && c < 64) return *m_casilla[c]; return *m_casilla[0];}

inline Empty	&Tablero::get_empty_cell(){return *m_empty;}
inline void Tablero::printPosibleMoves(int &&cell){ printPosibleMoves((*this)[cell]);}
inline int Tablero::getEvent(){return m_event;}
#endif
