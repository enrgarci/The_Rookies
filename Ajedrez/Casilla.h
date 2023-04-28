#ifndef CASILLA_H
#define CASILLA_H

class Pieza;
class Tablero;

#include "header.h"

class Casilla
{
friend Tablero;
private:
	int		m_id;
	int		m_move_calculation = -1;
	Pieza	*m_piece;
	bool	m_in_check = false;
	bool	m_can_en_passant = false;
	bool	m_posible_destination = false;
	vector<int> m_move_lst;
public:
	Casilla(Pieza *p, color c, int id);
	~Casilla();
	void			setCheck(bool inCheck);
	void			setId(int id);
	void			setPiece(Pieza &p);
	void			setPiece(figura f, color c);
	Pieza			&getPiece();
	bool			getCheck();
	int				getId();
	bool			getEnPassant();
	void			setEnPassant(bool c);
	bool			getPosMove();
	void			setPosMove(bool c);
	vector<int>		&getMoveList(Tablero &T);
	bool operator==(Casilla &a);
	bool operator!=(Casilla &a);
};

inline bool Casilla::operator==(Casilla &a){return this->m_id == a.m_id;}
inline bool Casilla::operator!=(Casilla &a){return this->m_id != a.m_id;}
#endif
