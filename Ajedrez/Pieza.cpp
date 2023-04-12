#include "Pieza.h"
#include "Casilla.h"
#include "Tablero.h"

color	Pieza::getColor(){return(col);}
figura	Pieza::getFig(){return(fig);}
void	Pieza::setFig(figura f){ fig = f;}
void	Pieza::setColor(color c){ col = c;}

void Empty::possible_moves(Tablero &board, Casilla &cell)
{	
	return;
}

char Empty::getSymbol() {return 0;}


/// @brief set cell true, if a king on cell could reach them
/// @todo look if move would be check, that ilegal!
void King::possible_moves(Tablero &board, Casilla &cell)
{	
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y) continue;
			Casilla &relative = board.get_cell(cell, x, y);
			if(relative != cell && board.can_Move_To(relative, cell))
				relative.setPosMove(true);
		}
	}
}

char King::getSymbol() {return (col == Blanco ? W_KING : B_KING);}
char Queen::getSymbol() {return (Rook::col == Blanco ? W_QUEEN : B_QUEEN);}
char Rook::getSymbol() {return (col == Blanco ? W_ROOK : B_ROOK);}
char Bishop::getSymbol() {return (col == Blanco ? W_BISHOP : B_BISHOP);}
char Knight::getSymbol() {return (col == Blanco ? W_KNIGHT : B_KNIGHT);}
char Pawn::getSymbol() {return (col == Blanco ? W_PAWN : B_PAWN);}

/// @brief set cells true, if a bishop on cell could reach them
void Bishop::possible_moves(Tablero &board, Casilla &cell)
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
				if (board.can_Move_To(relative, cell)) relative.setPosMove(true);
				if (!board.is_empty(relative)) reachWall[i] = true;
			}
			else {reachWall[i] = true; break;}
		}
	}
}

/// @brief set cells true, if a rook on cell could reach them
void Rook::possible_moves(Tablero &board, Casilla &cell)
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
				if (board.can_Move_To(relative, cell)) relative.setPosMove(true);
				if (!board.is_empty(relative)) reachWall[i] = true;
			}
			else {reachWall[i] = true; break;}
		}
	}
}

/// @brief set cells true, if a knight on cell could reach them
void Knight::possible_moves(Tablero &board, Casilla &cell)
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
					relative.setPosMove(true);
			}
		}
	}
}

void Pawn::possible_moves(Tablero &board, Casilla &cell)
{
	int dir = 1;
	if ((cell.getPiece()).getColor() == color::Blanco) dir = 1;
	if ((cell.getPiece()).getColor() == color::Negro) dir = -1;
	int	en_passant_row = dir > 0 ? 3 : 4; // filas centrales hay que ver si se puede tomar al paso
	int	jump_row = dir > 0 ? 6 : 1; // penultima fila de cada lado puede dar un salto

	//delante
	if (board.is_empty(board.get_cell(cell, 0, dir))) 
		board.get_cell(cell, 0, dir).setPosMove(true);			
	// Y  solo al empezar un salto puede dar !
	if (cell.getId() / 8 == jump_row && 
	board.is_empty(board.get_cell(cell, 0, dir)) && 
	board.is_empty(board.get_cell(cell, 0, 2 * dir))) 
		board.get_cell(cell, 0, 2 * dir).setPosMove(true);
	//capturas
	for (int i = -1; i < 2; i+=2)
	{
		if (board.is_enemy_piece(board.get_cell(cell, i, dir), cell.getPiece().getColor())) 
			board.get_cell(cell, i, dir).setPosMove(true);
	}
	// En passant
	for (int i = -1; i < 2; i+=2)
	{
		if (cell.getId() / 8 == en_passant_row && 
		board.is_enemy_piece(board.get_cell(cell, i, 0), (cell.getPiece()).getColor()) && 
		board.get_cell(cell, i, 0).getEnPassant()) 
			board.get_cell(cell, i, 0).setPosMove(true);
	}
}

/// @brief set cells true, if a queen on cell could reach them
void Queen::possible_moves(Tablero &board, Casilla &cell)
{
	Rook::possible_moves(board, cell);
	Bishop::possible_moves(board, cell);
}
