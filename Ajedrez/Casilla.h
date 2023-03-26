/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:15:45
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 18:12:16
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
	void	setCheck(bool inCheck);
	void	setPiece(Pieza::figura f);
	void	setColor(Pieza::color c);
	Pieza::figura	getPiece();
	Pieza::color	getColor();
	bool	getCheck();
};

#endif
