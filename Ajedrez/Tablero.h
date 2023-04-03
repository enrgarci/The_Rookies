#ifndef TABLERO_H
#define TABLERO_H


#include "header.h"
#include "Casilla.h"

using std::cout;
using std::endl;
using std::string;

const string INITIAL_POS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

 class Tablero
{
private:
	Casilla m_casilla[64];
	Casilla	m_last_move[2];				///#TODO
	Pieza::color	m_mueve;
	string	m_initial_board;
	string	m_game;						///TODO
	bool	m_can_castle = true;		///#TODO
	bool	m_can_en_passant = false;	///#TODO
	int		m_fifty_move_rule = 0;		///#TODO
	int		m_repeat_three = 0;			///#TODO
	friend	class Moves;						///#TODO
public:
	Tablero (string fen = INITIAL_POS);
	void	print();
	string	get_fen();
	Casilla get_cell(int x);
	Casilla get_cell(int x, int y);
	Casilla get_cell(char c, int y);
	Casilla get_cell(Casilla self, int relative_x, int relative_y);
	void	set_possible_moves(Casilla cell);
	void	reset_possible_moves();
	bool	can_Move_To(Casilla dst, Casilla src);
	bool	is_move_wall(Casilla dst, Casilla src);
	bool	is_empty(Casilla dst);
	bool	is_enemy_piece(Casilla dst, Pieza::color myColor);
	void	posible_king(Casilla cell);
	void	posible_queen(Casilla cell);
	void	posible_rook(Casilla cell);
	void	posible_bishop(Casilla cell);
	void	posible_knight(Casilla cell);
	void	posible_pawn(Casilla cell);
	void	printPosibleMoves (Casilla cell);
};

#endif
