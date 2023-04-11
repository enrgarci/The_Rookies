#ifndef CASILLA_H
#define CASILLA_H

class Pieza;
class Tablero;

#include "header.h"
#include <vector>

using std::vector;

class Casilla
{
private:
	int		m_id;
	Pieza	*m_piece;
	bool	m_in_check = false;
	bool	m_can_en_passant = false;
	bool	m_posible_destination = false;
	int		m_move_calculation = -1;
	vector<int> m_move_lst;
public:
	Casilla(Pieza *p, color c, int id);
	~Casilla();
	void			setCheck(bool inCheck);
	void			setId(int id);
	void			setPiece(Pieza &p);
	void			setPiece(figura f, color c);
	Pieza			*getPiece();
	bool			getCheck();
	int				getId();
	bool			getEnPassant();
	void			setEnPassant(bool c);
	bool			getPosMove();
	void			setPosMove(bool c);
	vector<int>		&getMoveList(Tablero &T);
};

#endif
