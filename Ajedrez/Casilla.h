/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:15:45
 //  Modified by: enrgarci
 //  Modified time: 2023-03-27 01:03:48
 //  Description:
 //
#ifndef CASILLA_H
#define CASILLA_H

#include "header.h"

 class Casilla
{
private:
	Pieza	m_piece;
	bool	m_in_check;
//	bool	m_is_highlighted;
public:
	void			setCheck(bool inCheck);
	void			setFigure(Pieza::figura f);
	void			setColor(Pieza::color c);
	void			setPiece(Pieza p);
	void			setPiece(Pieza::figura f, Pieza::color c);
	Pieza::figura	getFigure();
	Pieza::color	getColor();
	Pieza			getPiece();
	bool			getCheck();
};

#endif
