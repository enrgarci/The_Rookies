#ifndef PIEZA_H
#define PIEZA_H

#include "header.h"

class Tablero;
class Casilla;

/// @brief hola esto es un resumen
class Pieza
{
friend Tablero;
friend Casilla;
protected:
	vector<int>	possible_moves(Tablero &board, Casilla &cell);
public:
	virtual vector<int> pseudo_legal(Tablero &board, Casilla &cell) = 0;
	virtual ~Pieza() = default;
};

class Empty: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell)
	{vector<int> moves; moves.clear() ;return moves;};
};

class King: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};


class Rook: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};

class Bishop: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};

class Knight: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};

class Pawn: public Pieza
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};
#endif

class Queen: public Rook, public Bishop
{
public:
	vector<int> pseudo_legal(Tablero &board, Casilla &cell);
};
