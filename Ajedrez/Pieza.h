#ifndef PIEZA_H
#define PIEZA_H

#include "header.h"

class Tablero;
class Casilla;

/// @brief hola esto es un resumen
class Pieza
{
protected:
	figura fig;
	color	col;
public:
	virtual void	possible_moves(Tablero &board, Casilla &cell)=0;
	virtual char	getSymbol()=0;
	figura	getFig();
	color	getColor();
	void	setFig(figura f);
	void	setColor(color c);
};

class Empty: public Pieza
{
public:
	Empty();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class King: public Pieza
{
public:
	King();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Queen: public Pieza
{
public:
	Queen();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Rook: public Pieza
{
public:
	Rook();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Bishop: public Pieza
{
public:
	Bishop();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Knight: public Pieza
{
public:
	Knight();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Pawn: public Pieza
{
public:
	Pawn();
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};
#endif
