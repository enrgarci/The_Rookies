#include "Casilla.h"
#include "Pieza.h"
#include "Tablero.h"
#include "Partida.h"

Casilla::Casilla(Tablero &T, const Pieza *p, figura f, color c, int id)
{
	m_piece = (Pieza *) p;
	m_color = c;
	m_id = id;
	m_color = c;
	m_figure = f;
	this->setSymbol();
	m_parent_board = &T;
}

Casilla::~Casilla()
{
	m_id = -1;
}
void Casilla::setPiece(figura f, color c)
{
	m_figure = f;
	m_color = c;
}
vector<int>	&Casilla::getMoveList()
{
	//only play on the last position, can't play if reviewing a game :)
	if ( m_parent_board->move_count != ((*m_parent_board).m_parent_game->getCurrentPos()))
		{m_move_lst.clear();return m_move_lst;}
	Tablero &T = *m_parent_board;
	if (T.move_count == m_move_calculation) return m_move_lst;
	m_move_calculation = T.move_count;
	m_move_lst.clear();
	m_move_lst = m_piece->possible_moves(T, *this, 1);
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
bool Casilla::getCheck(color c)
{
	Tablero &T = *((m_parent_board)->m_parent_game->T);
	for (auto pos: c == Blanco ? T.m_b_pieces : T.m_w_pieces)
	{
		if (T.get_cell(pos).getFigura() == Rey ||
			T.get_cell(pos).getFigura() == Peon) continue;
		for (auto cell : T.get_pseudo_moves(pos))
			if (cell == (this->m_id)) return 1;
	}
	//Check by king
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y) continue;
			if (T.get_cell((*this), x,y).m_figure == Rey && T.get_cell((*this), x,y).m_color != c) return (m_in_check = true);
		}
	}
	//Check by pawn
	int dir =  (c == Blanco) ? 1 : -1;
	for (int i = -1; i < 2; i+=2)
		if (T.get_cell((*this), i,dir).m_figure == Peon && T.get_cell((*this), i,dir).m_color != c) return (m_in_check = true);
	return m_in_check = false, 0;
}
/// @brief Looks if a Piece is pinned or not
/// @param target The target square to see if moving there results or not end the check
/// @return 1 if movement between this and target results (or keeps) the check, 0 otherwise.
bool	Casilla::isPinned(const Casilla &target)
{
	Tablero &T = *m_parent_board;
	Tablero temp = Tablero(*(m_parent_board->m_parent_game), m_parent_board->get_fen());
	int		king_pos;
	bool	king_in_check;
	//find king
	for (auto piece : T.turn == Blanco ? T.m_w_pieces : T.m_b_pieces)
		if (T[piece].m_figure == Rey) king_pos = piece;
	//look if king is in check
	king_in_check =  T[king_pos].getCheck(T.turn);
	// if is not in check look if movement would result 
	if (!king_in_check)
	{
		temp.do_move(m_id, target.m_id, 1);
		if (temp[king_pos].getCheck(T.turn)) return 1;
		return 0;
	}
	else //if king in check look if movement would end the check
	{
		temp.do_move(m_id, target.m_id, 1);
		if (temp[king_pos].getCheck(T.turn)) return 1;
		return 0;
	}
}

