#ifndef CASILLA_H
#define CASILLA_H

class Pieza;

#include "header.h"

class Casilla
{
private:
	int		m_id;
	Pieza	*m_piece;
	bool	m_in_check = false;
	bool	m_can_en_passant = false;
	bool	m_posible_destination = false;
public:
	Casilla(Pieza *p, color c, int id);
	void			setCheck(bool inCheck);
	void			setId(int id);
	void			setFigure(figura f);
	void			setColor(color c);
	void			setPiece(Pieza &p);
	void			setPiece(figura f, color c);
	figura	getFigure();
	color	getColor();
	Pieza			getPiece();
	bool			getCheck();
	int				getId();
	bool			getEnPassant();
	void			setEnPassant(bool c);
	bool			getPosMove();
	void			setPosMove(bool c);
};

#endif
