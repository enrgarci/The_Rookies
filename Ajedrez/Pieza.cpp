#include "Pieza.h"
#include "Casilla.h"
#include "Tablero.h"

void Empty::possible_moves(Tablero &board, Casilla &cell, int pin)
{	
	return;
}
/// @brief set cell true, if a king on cell could reach them
/// @todo look if move would be check, that ilegal!
void King::possible_moves(Tablero &board, Casilla &cell, int pin)
{	
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y) continue;
			Casilla &relative = board.get_cell(cell, x, y);
			if(relative != cell &&
					board.can_Move_To(relative, cell) &&
					!relative.getCheck(cell.getColor()))
				relative.setPosMove(true);
		}
	}
	//Enroque
	if (!cell.getCheck(cell.getColor()))
	{
		//Color
		const int w_empty[6] = {57,58,59,60,61,62};
		const int b_empty[6] = {1,2,3,4,5,6};
		//enroque corto
		color c = cell.getColor();
		if (board.can_castle(c) == 1 ||
			board.can_castle(c) == 2 ) //no ha perdido los derechos de enroque
		{
			//vacío entre rey-torre
			if (board.is_empty(board[c == Blanco ? w_empty[4]: b_empty[4]]) && 
					board.is_empty(board[c == Blanco ? w_empty[5]: b_empty[5]]) &&
					!board[c == Blanco ? w_empty[4]: b_empty[4]].getCheck(c) && 
					!board[c == Blanco ? w_empty[5]: b_empty[5]].getCheck(c))
				board[c == Blanco ? w_empty[5]: b_empty[5]].setPosMove(true);
		}
		//enroque largo
		if (board.can_castle(c) == 0 ||
			board.can_castle(c) == 2 ) //no ha perdido los derechos de enroque
		{
			//vacío entre rey-torre
			if (board.is_empty(board[c == Blanco ? w_empty[0]: b_empty[0]]) && 
					board.is_empty(board[c == Blanco ? w_empty[1]: b_empty[1]]) && 
					board.is_empty(board[c == Blanco ? w_empty[2]: b_empty[2]]) &&
					!board[c == Blanco ? w_empty[1]: b_empty[1]].getCheck(c) && 
					!board[c == Blanco ? w_empty[2]: b_empty[2]].getCheck(c))
				board[c == Blanco ? w_empty[1]: b_empty[1]].setPosMove(true);
		}
	}
}

/// @brief set cells true, if a bishop on cell could reach them
void Bishop::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	int reachWall[4] = {0, 0, 0, 0}; // antihorario empezando por arriba
	int dir = 1;
	//the 4 directions
	for (int i = 0; i < 4; i++, dir = -dir)
	{
		//the distance 
		for(int dist = 1; dist < 8; dist++)
		{
			if (reachWall[i]) break;
			Casilla &relative = board.get_cell(cell, dist * dir, 
													dist * (dir * (i < 2) - dir * (i >= 2)));
			if (relative != cell)
			{
				if (board.can_Move_To(relative, cell))
				{
					if (!pin)
						relative.setPosMove(true);
					else if (pin && !cell.isPinned(relative))
						relative.setPosMove(true);
				}
				if (!board.is_empty(relative))
				{
					if (!(relative.getFigura() == Rey && relative.getColor() != cell.getColor()))
						reachWall[i] = true;
				}
			}
			else {reachWall[i] = true; break;}
		}
	}
}

/// @brief set cells true, if a rook on cell could reach them
void Rook::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	int reachWall[4] = {0, 0, 0, 0}; // antihorario empezando por arriba
	int dir = 1;
	//the 4 directions
	for (int i = 0; i < 4; i++, dir = -dir)
	{
		//the distance 
		for(int dist = 1; dist < 8; dist++)
		{
			if (reachWall[i]) break;
			Casilla &relative = board.get_cell(cell, dist * dir * (i < 2), 
													dist * dir * (i >= 2));
			if (relative != cell)
			{
				if (board.can_Move_To(relative, cell))
				{
					if (!pin)
						relative.setPosMove(true);
					else if (pin && !cell.isPinned(relative))
						relative.setPosMove(true);
				}
				if (!board.is_empty(relative))
				{
					if (!(relative.getFigura() == Rey && relative.getColor() != cell.getColor()))
						reachWall[i] = true;
				}
			}
			else {reachWall[i] = true; break;}
		}
	}
}

/// @brief set cells true, if a knight on cell could reach them
void Knight::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	for (int x = -2; x < 3; x++)
	{
		int y = 3 - abs(x);
		for (int i = -1; i < 2; i+=2)
		{
			if (!x) continue;
			Casilla &relative = board.get_cell(cell, x, y * i);
			if (relative != cell)
			{
				if (board.can_Move_To(relative, cell))	
				{
					if (!pin)
						relative.setPosMove(true);
					else if (pin && !cell.isPinned(relative))
						relative.setPosMove(true);
				}
			}
		}
	}
}

void Pawn::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	int dir = 1;
	if (cell.getColor() == color::Blanco) dir = 1;
	else if (cell.getColor() == color::Negro) dir = -1;
	int	en_passant_row = dir > 0 ? 3 : 4; // filas centrales hay que ver si se puede tomar al paso
	int	jump_row = dir > 0 ? 6 : 1; // penultima fila de cada lado puede dar un salto

	//delante
	if (board.is_empty(board.get_cell(cell, 0, dir))) 
	{
		if (!pin)
			board.get_cell(cell, 0, dir).setPosMove(true);
		else if(pin && !cell.isPinned(board.get_cell(cell, 0, dir)))
			board.get_cell(cell, 0, dir).setPosMove(true);
	}
	// Y  solo al empezar un salto puede dar !
	if (cell.getId() / 8 == jump_row && 
	board.is_empty(board.get_cell(cell, 0, dir)) && 
	board.is_empty(board.get_cell(cell, 0, 2 * dir))) 
	{
		if (!pin)
			board.get_cell(cell, 0, 2 * dir).setPosMove(true);
		else if(pin && !cell.isPinned(board.get_cell(cell, 0, 2 * dir)))
			board.get_cell(cell, 0, 2 * dir).setPosMove(true);
	}
	//capturas
	for (int i = -1; i < 2; i+=2)
	{
		if (board.is_enemy_piece(board.get_cell(cell, i, dir), cell.getColor()))
		{
			if (!pin)
				board.get_cell(cell, i, dir).setPosMove(true);
			else if(pin && !cell.isPinned(board.get_cell(cell, i, dir)))
				board.get_cell(cell, i, dir).setPosMove(true);
		}
	}
	// En passant
	for (int i = -1; i < 2; i+=2)
	{
		if (cell.getId() / 8 == en_passant_row && 
				board.get_cell(cell, i, dir).getEnPassant_move() == board.move_count &&
				board.get_cell(cell, i, dir).getEnPassant())
		{
			if (!pin)
				board.get_cell(cell, i, dir).setPosMove(true);
			else if(pin && !cell.isPinned(board.get_cell(cell, i, dir)))
				board.get_cell(cell, i, dir).setPosMove(true);
		}
	}
}

/// @brief set cells true, if a queen on cell could reach them
void Queen::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	Rook::possible_moves(board, cell, pin);
	Bishop::possible_moves(board, cell, pin);
}
