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
	virtual void	possible_moves(Tablero &board, Casilla &cell)=0;
public:
	virtual ~Pieza();
};

class Empty: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};

class King: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};


class Rook: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};

class Bishop: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};

class Knight: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};

class Pawn: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};
#endif

class Queen: public Rook, public Bishop
{
public:
	void possible_moves(Tablero &board, Casilla &cell);
};
