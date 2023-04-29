#ifndef CASILLA_H
#define CASILLA_H

class Pieza;
class Tablero;
class Casilla;
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
	figura	m_figure;
	color	m_color;
	char	m_symbol;
	Tablero *m_parent_board;
public:
	Casilla(Tablero &T,Pieza *p, figura f, color c, int id);
	~Casilla();
	void			setCheck(bool inCheck);
	void			setId(int id);
	void			setPiece(Pieza &p);
	void			setPiece(figura f, color c);
	void			setSymbol();
	char			getSymbol();
	Pieza			&getPiece();
	figura			getFigura();
	color			getColor();
	bool			getCheck();
	int				getId();
	bool			getEnPassant();
	void			setEnPassant(bool c);
	bool			getPosMove();
	void			setPosMove(bool c);
	void			clear();
	vector<int>		&getMoveList();
	bool operator==(Casilla &a);
	Casilla &operator=(const Casilla &a);
	bool operator!=(Casilla &a);
};

inline bool Casilla::operator==(Casilla &a){return this->m_id == a.m_id;}
inline bool Casilla::operator!=(Casilla &a){return this->m_id != a.m_id;}
inline figura Casilla::getFigura(){return m_figure;}
inline color Casilla::getColor(){return m_color;}
inline char Casilla::getSymbol(){return m_symbol;}
inline Pieza &Casilla::getPiece(){return *m_piece;}
inline void Casilla::setId(int id){m_id = id;}
inline int Casilla::getId(){return m_id;}
inline bool Casilla::getEnPassant(){return m_can_en_passant;}
inline void Casilla::setEnPassant(bool c){m_can_en_passant = c;}
inline bool Casilla::getPosMove(){return m_posible_destination;}
inline void Casilla::setPosMove(bool c){m_posible_destination = c;}
inline void Casilla::setCheck(bool inCheck) { m_in_check = inCheck; }
inline bool Casilla::getCheck() { return m_in_check; }
#endif
