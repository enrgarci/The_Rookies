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
	figura fig;
	color	col;
	virtual void	possible_moves(Tablero &board, Casilla &cell)=0;
public:
	Pieza(figura f, color c=noColor): fig(f), col(c){};
	virtual ~Pieza();
	virtual char	getSymbol()=0;
	figura	getFig();
	color	getColor();
	void	setFig(figura f);
	void	setColor(color c);
};

class Empty: public Pieza
{
public:
	Empty() : Pieza(Vacio, noColor){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class King: public Pieza
{
public:
	King() : Pieza(Rey){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};


class Rook: public Pieza
{
public:
	Rook(figura f=Torre) : Pieza(f){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Bishop: public Pieza
{
public:
	Bishop() : Pieza(Alfil){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Knight: public Pieza
{
public:
	Knight() : Pieza{Caballo}{};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};

class Pawn: public Pieza
{
public:
	Pawn() : Pieza(Peon){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};
#endif

class Queen: public Rook, public Bishop
{
public:
	Queen() : Rook(Reina){};
	void possible_moves(Tablero &board, Casilla &cell);
	char	getSymbol();
};
