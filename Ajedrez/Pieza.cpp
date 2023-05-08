#include "Pieza.h"
#include "Casilla.h"
#include "Tablero.h"

vector<int> Pieza::possible_moves(Tablero &board, Casilla &cell, int pin)
{
	vector<int> pseudo_moves, legal_moves;
	pseudo_moves = board.get_pseudo_moves(cell);
	for (int i = 0; i < pseudo_moves.size(); i++)
		if (!cell.isPinned(board[pseudo_moves.at(i)]) &&
			board[pseudo_moves.at(i)].getColor() != cell.getColor())
			legal_moves.push_back(pseudo_moves.at(i));
	return legal_moves;
}
vector<int> Rook::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves;
	int reachWall[4] = {0, 0, 0, 0}; // antihorario empezando por arriba
	int dir = 1;
	// the 4 directions
	for (int i = 0; i < 4; i++, dir = -dir)
	{
		bool found_king = false;
		// the distance
		for (int dist = 1; dist < 8; dist++)
		{
			Casilla &relative = board.get_cell(cell, dist * dir * (i < 2),
											   dist * dir * (i >= 2));
			if (relative != cell)
			{
				if (relative.getFigura() == Vacio)
					moves.push_back(relative.getId());
				else
				{
					reachWall[i] = true;
					if (!found_king)
						moves.push_back(relative.getId());
					if ((relative.getFigura() == Rey && (relative.getColor() != cell.getColor())))
						found_king = true, reachWall[i] = false;
				}
			}
			else
				break;
			if (reachWall[i])
				break;
		}
	}
	return moves;
}

vector<int> Queen::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves, bishop_moves;
	moves = Rook::pseudo_legal(board, cell);
	bishop_moves = Bishop::pseudo_legal(board, cell);
	moves.insert(moves.end(), bishop_moves.begin(), bishop_moves.end());
	return moves;
}

vector<int> Pawn::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves;
	int dir = 1;
	if (cell.getColor() == color::Blanco)
		dir = 1;
	else if (cell.getColor() == color::Negro)
		dir = -1;
	int en_passant_row = dir > 0 ? 3 : 4; // filas centrales hay que ver si se puede tomar al paso
	int jump_row = dir > 0 ? 6 : 1;		  // penultima fila de cada lado puede dar un salto

	// delante y salto al comenzar
	for (int i = 1; i < 3; i++)
	{
		if (i == 2 && cell.getId() / 8 != jump_row)
			break;
		if (board.is_empty(board.get_cell(cell, 0, i * dir)))
			moves.push_back(board.get_cell(cell, 0, i * dir).getId());
		else
			break;
	}
	// En passant && capturas
	for (int i = -1; i < 2; i += 2)
	{
		if (!board.is_empty(board.get_cell(cell, i, dir)) ||
			cell.getId() / 8 == en_passant_row &&
				board.get_cell(cell, i, dir).getEnPassant_move() == board.move_count &&
				board.get_cell(cell, i, dir).getEnPassant())
			moves.push_back(board.get_cell(cell, i, dir).getId());
	}
	return moves;
}

vector<int> Knight::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves;
	for (int x = -2; x < 3; x++)
	{
		int y = 3 - abs(x);
		for (int i = -1; i < 2; i += 2)
		{
			if (!x)
				continue;
			Casilla &relative = board.get_cell(cell, x, y * i);
			if (relative != cell)
				moves.push_back(relative.getId());
		}
	}
	return moves;
}

vector<int> Bishop::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves;
	int reachWall[4] = {0, 0, 0, 0}; // antihorario empezando por arriba
	int dir = 1;
	// the 4 directions
	for (int i = 0; i < 4; i++, dir = -dir)
	{
		bool found_king = false;
		// the distance
		for (int dist = 1; dist < 8; dist++)
		{
			Casilla &relative = board.get_cell(cell, dist * dir,
											   dist * (dir * (i < 2) - dir * (i >= 2)));
			if (relative != cell)
			{
				if (relative.getFigura() == Vacio)
					moves.push_back(relative.getId());
				else
				{
					reachWall[i] = true;
					if (!found_king)
						moves.push_back(relative.getId());
					if ((relative.getFigura() == Rey && (relative.getColor() != cell.getColor())))
						found_king = true, reachWall[i] = false;
				}
			}
			else
				break;
			if (reachWall[i])
				break;
		}
	}
	return moves;
}

vector<int> King::pseudo_legal(Tablero &board, Casilla &cell)
{
	vector<int> moves;
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y)
				continue;
			Casilla &relative = board.get_cell(cell, x, y);
			if (relative != cell &&
				board.can_Move_To(relative, cell))
				moves.push_back(relative.getId());
		}
	}
	// Enroque
	// Color
	const int w_empty[6] = {57, 58, 59, 60, 61, 62};
	const int b_empty[6] = {1, 2, 3, 4, 5, 6};
	// enroque corto
	color c = cell.getColor();
	if (board.can_castle(c) == 1 ||
		board.can_castle(c) == 2) // no ha perdido los derechos de enroque
	{
		// vacío entre rey-torre
		if (board.is_empty(board[c == Blanco ? w_empty[4] : b_empty[4]]) &&
			board.is_empty(board[c == Blanco ? w_empty[5] : b_empty[5]]) &&
			!board[c == Blanco ? w_empty[4] : b_empty[4]].getCheck(c) &&
			!board[c == Blanco ? w_empty[5] : b_empty[5]].getCheck(c))
			moves.push_back(board[c == Blanco ? w_empty[5] : b_empty[5]].getId());
	}
	// enroque largo
	if (board.can_castle(c) == 0 ||
		board.can_castle(c) == 2) // no ha perdido los derechos de enroque
	{
		// vacío entre rey-torre
		if (board.is_empty(board[c == Blanco ? w_empty[0] : b_empty[0]]) &&
			board.is_empty(board[c == Blanco ? w_empty[1] : b_empty[1]]) &&
			board.is_empty(board[c == Blanco ? w_empty[2] : b_empty[2]]) &&
			!board[c == Blanco ? w_empty[1] : b_empty[1]].getCheck(c) &&
			!board[c == Blanco ? w_empty[2] : b_empty[2]].getCheck(c))
			moves.push_back(board[c == Blanco ? w_empty[1] : b_empty[1]].getId());
	}
	return moves;
}
