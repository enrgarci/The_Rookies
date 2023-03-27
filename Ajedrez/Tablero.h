/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-28 01:37:00
 //  Description:
 //
 
#ifndef TABLERO_H
#define TABLERO_H

#include "header.h"
#include "Casilla.h"

using std::cout;
using std::endl;
using std::string;

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
	Tablero (string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	void	print();
	string	get_fen();
	Casilla get_cell(int x);
	Casilla get_cell(int x, int y);
	Casilla get_cell(char c, int y);
	Casilla get_cell(Casilla self, int relative_x, int relative_y);
	void	set_possible_moves(Casilla cell);
	void	reset_possible_moves();
	bool	can_Move_To(Casilla dst, Casilla src);
	void	posible_king(Casilla cell);
	void	posible_queen(Casilla cell);
	void	posible_rook(Casilla cell);
	void	posible_bishop(Casilla cell);
	void	posible_knight(Casilla cell);
	void	posible_pawn(Casilla cell);
	void	printPosibleMoves (Casilla cell);
};

#endif
