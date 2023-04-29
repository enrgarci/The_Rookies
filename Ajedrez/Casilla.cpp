#include "Casilla.h"
#include "Pieza.h"
#include "Tablero.h"

Casilla::Casilla(Tablero &T, Pieza *p, figura f, color c, int id)
{
	m_piece = p;
	m_color = c;
	m_id = id;
	m_color = c;
	m_figure = f;
	this->setSymbol();
	m_parent_board = &T;
}

Casilla::~Casilla()
{
}
void Casilla::setPiece(figura f, color c)
{
	m_figure = f;
	m_color = c;
}
vector<int>	&Casilla::getMoveList()
{
	Tablero &T = *m_parent_board;
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

void Casilla::setSymbol()
{
	switch (m_figure)
	{
	case Rey:
		m_symbol = 'K';
		break;
	case Reina:
		m_symbol = 'Q';
		break;
	case Torre:
		m_symbol = 'R';
		break;
	case Alfil:
		m_symbol = 'B';
		break;
	case Caballo:
		m_symbol = 'N';
		break;
	case Peon:
		m_symbol = 'P';
		break;	
	case Vacio:
		m_symbol = 0;
		break;
	default:
		break;
	}
	if (m_color == Negro && m_symbol != Vacio)
		m_symbol += 32; //to upper
}
/// @brief Defines the = operator between Casillas, sets this Casilla with the same 
/// piece specific parameters, the ones dependant on board situation are not copied, as
/// they will be recalculated.
Casilla &Casilla::operator=(const Casilla &a)
{
	this->m_piece = a.m_piece;
	this->m_figure = a.m_figure;
	this->m_color = a.m_color;
	this->setSymbol();
	return *this;
}

void Casilla::clear()
{
	this->m_figure = Vacio;
	this->m_color = noColor;
	this->m_piece = &m_parent_board->get_empty_cell();
	this->m_symbol = 0;
}
