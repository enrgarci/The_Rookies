#include "Casilla.h"
#include "Pieza.h"

Casilla::Casilla(Pieza *p, color c, int id)
{
	m_piece = p;
	m_id = id;
}
Casilla::~Casilla()
{
	delete (m_piece);
}
inline void Casilla::setCheck(bool inCheck) { m_in_check = inCheck; }
inline bool Casilla::getCheck() { return m_in_check; }
inline void Casilla::setPiece(Pieza &p) { (*m_piece) = p; }
inline void Casilla::setPiece(figura f, color c)
{
	(*m_piece).setFig(f);
	(*m_piece).setColor(c);
}
inline void Casilla::setId(int id) { m_id = id; }
inline int Casilla::getId() { return m_id; }
inline bool Casilla::getEnPassant() { return m_can_en_passant; }
inline void Casilla::setEnPassant(bool c) { m_can_en_passant = c; }
inline bool Casilla::getPosMove() { return m_posible_destination; }
inline void Casilla::setPosMove(bool c) { m_posible_destination = c; }
