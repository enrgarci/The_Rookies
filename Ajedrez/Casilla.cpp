#include "Casilla.h"
#include "Pieza.h"
#include "Tablero.h"
#include "Partida.h"

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
	//only play on the last position, can't play if reviewing a game :)
	if ( m_parent_board->get_fen() != ((*m_parent_board).m_parent_game->positions.back()) ||
			m_parent_board->m_event > 1)
		{m_move_lst.clear();return m_move_lst;}
	Tablero &T = *m_parent_board;
	if (T.move_count == m_move_calculation) return m_move_lst;
	m_move_calculation = T.move_count;
	m_move_lst.clear();
	T.reset_possible_moves();
	m_piece->possible_moves(T, *this, 1);
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
bool Casilla::getCheck(color c)
{
	Tablero T = Tablero(*(m_parent_board->m_parent_game), m_parent_board->get_fen());
	if (T.move_count == m_check_calculation) return m_in_check;
	m_check_calculation = T.move_count;
	T.reset_possible_moves();
	//Check by rook || queen_line
	T.m_rook->possible_moves(T, *(new Casilla(T,T.m_rook,Torre,c, m_id)),0);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (T[i].m_posible_destination && &(T[i].getPiece()) == T.m_rook) return (m_in_check = true);
		if (T[i].m_posible_destination && &(T[i].getPiece()) == static_cast<Rook*>(T.m_queen)) return (m_in_check = true);
	}
	T.reset_possible_moves();
	//Check by bishop || queen_diagonal
	T.m_bishop->possible_moves(T, *(new Casilla(T,T.m_bishop,Alfil,c, m_id)),0);
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (T[i].m_posible_destination && &(T[i].getPiece()) == T.m_bishop) return (m_in_check = true);
		if (T[i].m_posible_destination && &(T[i].getPiece()) == static_cast<Rook*>(T.m_queen)) return (m_in_check = true);
	}
	T.reset_possible_moves();
	//Check by Knight
	T.m_knight->possible_moves(T, *(new Casilla(T,T.m_knight,Caballo,c, m_id)),0);
	for (int i = 0; i < BOARD_SIZE; i++)
		if (T[i].m_posible_destination && &(T[i].getPiece()) == T.m_knight) return (m_in_check = true);
	T.reset_possible_moves();
	//Check by king
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y) continue;
			if (T.get_cell((*this), x,y).m_figure == Rey && T.get_cell((*this), x,y).m_color != c) return (m_in_check = true);
		}
	}
	T.reset_possible_moves();
	//Check by pawn
	int dir =  (c == Blanco) ? 1 : -1;
	for (int i = -1; i < 2; i+=2)
		if (T.get_cell((*this), i,dir).m_figure == Peon && T.get_cell((*this), i,dir).m_color != c) return (m_in_check = true);
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
		temp.do_move(m_id, target.m_id);
		if (temp[king_pos].getCheck(T.turn)) return 1;
		return 0;
	}
	else //if king in check look if movement would end the check
	{
		temp.do_move(m_id, target.m_id);
		if (temp[king_pos].getCheck(T.turn)) return 1;
		return 0;
	}
}

