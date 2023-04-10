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
			Casilla *relative = board.get_cell(cell, x, y);
			if(relative->getId() >= 0 && board.can_Move_To(*relative, cell))
				relative->setPosMove(true);
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
	int reachWall[4] = {0, 0, 0, 0};
	int dir = 0; // seleccionar cuadrante para una vez que choca no pueda atravesar
	
	for (int x = 1; x < 8; x++)
	{
		for(int i = -1; i < 2; i+= 2)
		{
			for (int j = -1; j < 2; j+= 2)
			{
				if (j > 0 && i > 0) dir = 0;
				else if (j < 0 && i > 0) dir = 1;
				else if (j < 0 && i < 0) dir = 2;
				else if (j > 0 && i < 0) dir = 3;
				if (reachWall[dir] || !x) continue;
				Casilla *relative = board.get_cell(cell, x * j, x * i);
				if (relative->getId() >= 0)
				{
					if (board.can_Move_To(*relative, cell))
						relative->setPosMove(true);
					if (!board.is_empty(*relative)) reachWall[dir] = true;
				}
				else reachWall[dir] = true;
			}
		}
	}
}

/// @brief set cells true, if a rook on cell could reach them
void Rook::possible_moves(Tablero &board, Casilla &cell)
{
	int reachWall[4] = {0, 0, 0, 0}; // antihorario empezando por arriba
	int dir = 0; // seleccionar cuadrante para una vez que choca no puesda atravesar
	
	for (int x = 1; x < 8; x++)
	{
		// i  is for the positive or negative relative coordinates
		for(int i = -1; i < 2; i+= 2)
		{
			// j selects between vertical or horizontal
			for (int j = 0; j < 2; j++)
			{
				if (i > 0 && j) dir = 0;
				else if (i < 0 && !j) dir = 1;
				else if (i < 0 && j) dir = 2;
				else if (i > 0 && !j) dir = 3;
				if (reachWall[dir] || !x) continue;
				Casilla *relative = board.get_cell(cell, x * i * j, x * i * !j);
				if (relative->getId() >= 0)
				{
					if (board.can_Move_To(*relative, cell))
						relative->setPosMove(true);
					if (!board.is_empty(*relative)) reachWall[dir] = true;
				}
				else reachWall[dir] = true;
			}
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
			Casilla *relative = board.get_cell(cell, x, y * i);
			if (relative->getId() >= 0)
			{
				if (board.can_Move_To(*relative, cell))	
					relative->setPosMove(true);
			}
		}
	}
}

void Pawn::possible_moves(Tablero &board, Casilla &cell)
{
	int dir = 1;
	if ((*cell.getPiece()).getColor() == color::Blanco) dir = 1;
	if ((*cell.getPiece()).getColor() == color::Negro) dir = -1;
	int	en_passant_row = dir > 0 ? 3 : 4; // filas centrales hay que ver si se puede tomar al paso
	int	jump_row = dir > 0 ? 6 : 1; // penultima fila de cada lado puede dar un salto

	//delante
	if (board.is_empty(*board.get_cell(cell, 0, dir))) 
		board.get_cell(cell, 0, dir)->setPosMove(true);
	// Y  solo al empezar un salto puede dar !
	if (cell.getId() / 8 == jump_row && 
	board.is_empty(*board.get_cell(cell, 0, dir)) && 
	board.is_empty(*board.get_cell(cell, 0, 2 * dir))) 
		{board.get_cell(cell, 0, 2 * dir)->setPosMove(true);}
	//capturas
	for (int i = -1; i < 2; i+=2)
	{
		if (board.is_enemy_piece(*board.get_cell(cell, i, dir), (*cell.getPiece()).getColor())) 
		board.get_cell(cell, i, dir)->setPosMove(true);
	}
	// En passant
	for (int i = -1; i < 2; i+=2)
	{
		if (cell.getId() / 8 == en_passant_row && 
		board.is_enemy_piece(*board.get_cell(cell, i, 0), (*cell.getPiece()).getColor()) && 
		board.get_cell(cell, i, 0)->getEnPassant()) 
			board.get_cell(cell, i, 0)->setPosMove(true);
	}
}

/// @brief set cells true, if a queen on cell could reach them
void Queen::possible_moves(Tablero &board, Casilla &cell)
{
	Rook::possible_moves(board, cell);
	Bishop::possible_moves(board, cell);
}
