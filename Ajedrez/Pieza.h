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
	virtual void	possible_moves(Tablero &board, Casilla &cell, int pin)=0;
public:
	virtual ~Pieza() = default;
};

class Empty: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};

class King: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};


class Rook: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};

class Bishop: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};

class Knight: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};

class Pawn: public Pieza
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};
#endif

class Queen: public Rook, public Bishop
{
public:
	void possible_moves(Tablero &board, Casilla &cell, int pin);
};
