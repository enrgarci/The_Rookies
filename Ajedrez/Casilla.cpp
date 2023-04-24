#include "Casilla.h"
#include "Pieza.h"
#include "Tablero.h"
#include <algorithm>

Casilla::Casilla(Pieza *p, color c, int id)
{
	m_piece = p;
	m_piece->setColor(c);
	m_id = id;
}
Casilla::~Casilla()
{
}
void Casilla::setCheck(bool inCheck) { m_in_check = inCheck; }
bool Casilla::getCheck() { return m_in_check; }
void Casilla::setPiece(Pieza &p) { (*m_piece) = p; }
void Casilla::setPiece(figura f, color c)
{
	(*m_piece).setFig(f);
	(*m_piece).setColor(c);
}
Pieza &Casilla::getPiece(){return *m_piece;}
void Casilla::setId(int id) { m_id = id; }
int Casilla::getId() { return m_id; }
bool Casilla::getEnPassant() { return m_can_en_passant; }
void Casilla::setEnPassant(bool c) { m_can_en_passant = c; }
bool Casilla::getPosMove() { return m_posible_destination; }
void Casilla::setPosMove(bool c) { m_posible_destination = c; }
vector<int>	&Casilla::getMoveList(Tablero &T)
{
	if (T.move_count == m_move_calculation) return m_move_lst;
	m_move_calculation = T.move_count;
	m_move_lst.clear();
	T.reset_possible_moves();
	m_piece->possible_moves(T, *this);
	for (int i = 0; i < BOARD_SIZE; i++)
		if (T[i].m_posible_destination)
			m_move_lst.push_back(i);
	T.reset_possible_moves();
	return m_move_lst;
}
