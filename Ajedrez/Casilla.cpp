#include "Casilla.h"
#include "Pieza.h"
#include "Tablero.h"
#include "Partida.h"
#include "math.h"

Casilla::Casilla(Tablero &T, const Pieza *p, figura f, color c, int id)
{
	m_piece = (Pieza *)p;
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
vector<int> &Casilla::getMoveList()
{
	// only play on the last position, can't play if reviewing a game :)
	if (m_parent_board->move_count != ((*m_parent_board).m_parent_game->getCurrentPos()))
	{
		m_move_lst.clear();
		return m_move_lst;
	}
	Tablero &T = *m_parent_board;
	m_move_calculation = T.move_count;
	m_move_lst.clear();
	m_move_lst = m_piece->possible_moves(T, *this);
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
		m_symbol += 32; // to upper
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
	for (auto pos : c == Blanco ? T.m_b_pieces : T.m_w_pieces)
	{
		if (T.get_cell(pos).getFigura() == Rey ||
			T.get_cell(pos).getFigura() == Peon)
			continue;
		for (auto cell : T.get_pseudo_moves(pos))
			if (cell == (this->m_id))
				return 1;
	}
	// Check by king
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y)
				continue;
			if (T.get_cell((*this), x, y).m_figure == Rey && T.get_cell((*this), x, y).m_color != c)
				return (m_in_check = true);
		}
	}
	// Check by pawn
	int dir = (c == Blanco) ? 1 : -1;
	for (int i = -1; i < 2; i += 2)
		if (T.get_cell((*this), i, dir).m_figure == Peon && T.get_cell((*this), i, dir).m_color != c)
			return (m_in_check = true);
	return m_in_check = false, 0;
}

static vector<int> getDiagonal(int first, int second)
{
	vector<int> casillasEnDiagonal;
	int dx = (second % ROW_SIZE > first % ROW_SIZE) ? 1 : -1;
	int dy = (second / ROW_SIZE > first / ROW_SIZE) ? ROW_SIZE : -ROW_SIZE;
	for (int i = first + dx + dy; i != second; i += dx + dy)
		casillasEnDiagonal.push_back(i);
	return casillasEnDiagonal;
}

static vector<int> getRowCol(int first, int second)
{
	vector<int> casillaEnRowCol;
	int dx = (second % ROW_SIZE > first % ROW_SIZE) ? 1 : -1;
	int dy = (second / ROW_SIZE > first / ROW_SIZE) ? ROW_SIZE : -ROW_SIZE;
	if (second % ROW_SIZE == first % ROW_SIZE)
		dx = 0;
	if (second / ROW_SIZE == first / ROW_SIZE)
		dy = 0;
	for (int i = first + dx + dy; i != second; i += dx + dy)
		casillaEnRowCol.push_back(i);
	return casillaEnRowCol;
}
/// @brief Looks if a Piece is pinned or not
/// @param target The target square to see if moving there results or not end the check
/// @return 1 if movement between this and target results (or keeps) the check, 0 otherwise.
bool Casilla::isPinned(const Casilla &target)
{
	Tablero &T = *m_parent_board;
	int king_pos;
	bool result = false;
	bool king_check = false;
	// find king
	for (auto piece : T.turn == Blanco ? T.m_w_pieces : T.m_b_pieces)
	{
		if (T[piece].m_figure == Rey)
			king_pos = piece;
	}
	king_check = T[king_pos].getCheck(T.turn == Blanco ? Negro : Blanco);
	vector<int> potential_pin;
	// piezas enemigas en potencial pin
	for (int piece : T.turn == Blanco ? T.m_b_pieces : T.m_w_pieces)
	{
		if (T[piece].m_figure == Peon || T[piece].m_figure == Caballo || T[piece].m_figure == Rey)
			continue;
		if (T[piece].m_figure == Torre)
		{
			// misma columna o misma fila
			if (piece / 8 == king_pos / 8 || piece % 8 == king_pos % 8)
				potential_pin.push_back(piece);
		}
		else if (T[piece].m_figure == Alfil)
		{
			// misma diagonal
			if (abs((int)((piece % 8) - (int)(king_pos % 8))) == abs((int)(7 - piece / 8) - (int)(7 - king_pos / 8)))
				potential_pin.push_back(piece);
		}
		else if (T[piece].m_figure == Reina)
		{
			if (abs((int)((piece % 8) - (int)(king_pos % 8))) == abs((int)(7 - piece / 8) - (int)(7 - king_pos / 8)) ||
				piece / 8 == king_pos / 8 || piece % 8 == king_pos % 8)
				potential_pin.push_back(piece);
		}
	}
	bool diagonal = true;
	// vemos si hay linea de visión al hacer el movimiento o no,
	// rey en jaque (comprobar si que no es doble)
	int num_checks = 0;
	int checking_piece = -1;
	for (auto piece : T.turn == Blanco ? T.m_b_pieces : T.m_w_pieces)
	{
		for (auto poss_cell : T.get_pseudo_moves(piece))
		{
			if (poss_cell == king_pos)
			{
				checking_piece = piece;
				num_checks++;
				break;
			}
		}
		if (num_checks > 1)
			break;
	}
	// si no se encuentra m_target clavado
	// no jaque
	// si se encuentra m_id y no target, clavado
	int to = ((Casilla)target).getId();
	for (auto pinning_piece : potential_pin)
	{
		if (num_checks > 1) // jaque doble, solo puedo mover rey
		{
			if (m_id == king_pos && !T[to].getCheck(m_color))
				return false;
			return true;
		}
		vector<int> line;
		if (pinning_piece % ROW_SIZE == king_pos % ROW_SIZE ||
			pinning_piece / ROW_SIZE == king_pos / ROW_SIZE)
		{
			diagonal = false;
			line = getRowCol(king_pos, pinning_piece);
		}
		else
			line = getDiagonal(king_pos, pinning_piece);
		// no en jaque
		if (num_checks == 0)
		{
			if (m_id == king_pos)
			{
				if (!T[to].getCheck(m_color))
					return false;
				return true;
			}
			// pieza que no sea el que está clavando (del otro equipo) no hay pin
			// o del equipo, pero no la estudiada
			for (auto cell : line)
			{
				if ((T[cell].getColor() == T[king_pos].getColor() && cell != m_id))
				{
					result = false;
					break;
				}
				else if ((T[cell].getColor() != T[king_pos].getColor() && cell != pinning_piece) &&
						 T[cell].getColor() != noColor)
				{
					int dir = T.turn == Blanco ? 8 : -8;
					if (m_figure == Peon && target.m_en_passant_move == T.move_count) // si el movimiento fue tomar al paso
						if (cell == to + dir)
							continue;
					result = false;
					break;
				}
				else if (cell == to || to == pinning_piece)
				{
					result = false;
					break;
				}
				else
					result = true;
			}
		}
		else if (num_checks == 1)
		{
			if (m_id == king_pos)
			{
				if (!T[to].getCheck(m_color))
					return false;
				return true;
			}
			result = true;
			if (checking_piece == pinning_piece)
				for (auto cell : line)
					if (cell == to || to == checking_piece)
						return false;
				if (to == checking_piece)
						return false;
		}
	}
	if (potential_pin.size() == 0)
	{
		if (num_checks != 0)
		{
			if (m_id == king_pos)
			{
				if (!T[to].getCheck(m_color))
					return false;
				return true;
			}
			if (num_checks > 1)
				return true;
			result = true;
			if (to == checking_piece)
				result = false;
		}
		else
		{
			if (m_id == king_pos)
			{
				if (!T[to].getCheck(m_color))
					return false;
				return true;
			}
			result = false;
		}
	}
	return result;
}
