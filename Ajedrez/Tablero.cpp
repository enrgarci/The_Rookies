#include "Tablero.h"
#include "Casilla.h"
#include "Pieza.h"
#include "Partida.h"
#include <math.h>

// One object per piece type
/// @brief Reads a FEN position for the board initial position
/// @param fen the FEN value, should contain position  and turn only, no castling rights etc..
/// FEN @link ://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation

King* Tablero::s_king = nullptr;
Queen* Tablero::s_queen = nullptr;
Rook* Tablero::s_rook = nullptr;
Knight* Tablero::s_knight = nullptr;
Bishop* Tablero::s_bishop = nullptr;
Pawn* Tablero::s_pawn = nullptr;
Empty* Tablero::s_empty = nullptr;

Tablero::Tablero(Partida& p, string fen)
{

	int cell = 0;
	int all_pos = 0; // flag to check if FEN is complete
	bool complete_move = false;
	bool complete_move_count = false;
	bool complete_50_rule = false;
	char column = 0;

	m_parent_game = &p;
	// Read the FEN
	for (char c : fen)
	{
		// Non-Piece FEN characters
		if (c == 'w')
		{
			turn = color::Blanco;
			continue;
		}
		if (all_pos == 1 && c == 'b')
		{
			turn = color::Negro;
			continue;
		}
		if (c == '/' || c == '-')
		{
			continue;
		}
		if (c == ' ')
		{
			all_pos++;
			continue;
		}
		// enroque
		if (all_pos == 2 && c == 'Q')
		{
			m_w_castle_rights[0] = true;
			continue;
		}
		if (all_pos == 2 && c == 'K')
		{
			m_w_castle_rights[1] = true;
			continue;
		}
		if (all_pos == 2 && c == 'q')
		{
			m_b_castle_rights[0] = true;
			continue;
		}
		if (all_pos == 2 && c == 'k')
		{
			m_b_castle_rights[1] = true;
			continue;
		}
		// 50 move rule
		if (all_pos == 4 && !complete_50_rule)
		{
			m_fifty_move_rule = c - '0';
			complete_50_rule = true;
			continue;
		}
		if (all_pos == 4 && complete_50_rule)
		{
			m_fifty_move_rule = m_fifty_move_rule * 10 + c - '0';
			continue;
		}
		// move count
		if (all_pos == 5 && !complete_move_count)
		{
			move_count = c - '0';
			complete_move_count = true;
			continue;
		}
		if (all_pos == 5)
		{
			move_count = move_count * 10 + c - '0';
			continue;
		}
		// al paso
		if (all_pos == 3 && !complete_move)
		{
			column = c, complete_move = true;
			continue;
		}
		if (all_pos == 3 && complete_move)
		{
			(this->get_cell(column, c - '0')).m_can_en_passant = true;
			continue;
		}
		if (c >= '1' && c <= '8')
		{
			// we have c as char, (c - '0') = c as int
			for (int i = 0; i < (c - '0'); i++)
			{
				m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_empty, Vacio, noColor, cell);
				cell++;
			}
			continue;
		}
		// minuscula es negro
		color col = c >= 'a' ? Negro : Blanco;
		// Set pieces
		switch (c)
		{
			// black
		case 'R':
		case 'r':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_rook, Torre, col, cell);
			break;
		case 'N':
		case 'n':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_knight, Caballo, col, cell);
			break;
		case 'B':
		case 'b':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_bishop, Alfil, col, cell);
			break;
		case 'Q':
		case 'q':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), static_cast<Rook*>(s_queen), Reina, col, cell);
			break;
		case 'K':
		case 'k':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_king, Rey, col, cell);
			break;
		case 'P':
		case 'p':
			m_casilla[cell] = new Casilla(*(this->m_parent_game->T), s_pawn, Peon, col, cell);
			break;
		default:
			break;
		}
		cell++;
	}
	// change move_count format to half-moves
	// 11223344.. Is the FEN format, complete moves, we use 01234567...
	move_count = turn == Blanco ? (2 * move_count - 2) : (2 * move_count - 1);
	m_parent_game->setCurrentPos(move_count);
	// Default coronacion
	setCoronacion(Reina);
	// List of pieces of each colors
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].getColor() == Blanco)
			m_w_pieces.push_back(i);
		else if ((*this)[i].getColor() == Negro)
			m_b_pieces.push_back(i);
		// update if there was enpassant to correct move_count
		if ((*this)[i].m_can_en_passant == true)
			(*this)[i].m_en_passant_move = move_count;
	}
}

/// @brief Libera la memoria reservada para la clase @ref Tablero
Tablero::~Tablero()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		delete m_casilla[i];
	}
}
/// @brief Prints a console representation of the board
void Tablero::print()
{
	const int UnicodeVal = 9812;
	const int NumOfPieces = 6;

	setlocale(LC_ALL, "en_US.UTF-8");
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (!(i % 8))
			cout << (i + 1) / 8;
		Casilla& cell = *m_casilla[i];
		int pieceVal = int(cell.m_figure);
		int colorVal = int(cell.m_color);
		pieceVal = colorVal == 1 ? pieceVal + NumOfPieces : pieceVal;  // blanco o negro
		pieceVal = pieceVal == 0 ? (-UnicodeVal + '_') : pieceVal - 1; // si está vacio -> espacio
		wprintf(L"%lc", UnicodeVal + pieceVal);
		if (!((i + 1) % 8))
			cout << endl;
		if (i == 63)
			cout << " abcdefgh";
	}
	cout << endl
		<< "Turno de " << (turn == Blanco ? "Blancas" : "Negras") << endl
		<< "========" << endl;
}
/// @brief Prints a console representation of the possible moves of the @ref Piece contained on cell
void Tablero::printPosibleMoves(Casilla& cell)
{
	int cell_count = 0;
	vector<int> moves;
	moves = cell.getMoveList();
	setlocale(LC_ALL, "en_US.UTF-8");
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		int pieceVal;
		bool b = false;
		for (auto a : moves)
			if (a == i)
			{
				b = true;
				break;
			}
		pieceVal = b ? 'x' : ' '; // si es posible moverse marca
		wprintf(L"%lc", '0' + b);
		if (!(++cell_count % 8))
			cout << endl;
	}
	cout << endl;
	this->reset_possible_moves();
}
/// @brief Gets the FEN code of the current board state
/// @return FEN code as string
/// FEN: @link https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
string Tablero::get_fen()
{
	string fen = "";
	bool empty = false;
	int empty_count = 0;
	int cell_count = 0;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla& cell = *m_casilla[i];
		// empty cell management
		empty = is_empty(cell); // cell.getFigure() == figura::Vacio ? true : false;
		if (empty)
			empty_count++;
		if (!empty && empty_count)
			fen += (char)('0' + empty_count), empty_count = 0;
		// cell with piece
		if (!empty)
			fen += cell.getSymbol();
		// end of board row management
		if (!(++cell_count % ROW_SIZE))
		{
			if (empty_count)
			{
				fen += (char)('0' + empty_count);
				empty = false;
				empty_count = 0;
			}
			if (cell_count < BOARD_SIZE)
				fen += '/';
		}
	}
	// add turn
	fen += turn == Blanco ? " b " : " w ";
	// add castleling
	if (m_w_castle_rights[1])
		fen += "K";
	if (m_w_castle_rights[0])
		fen += "Q";
	if (m_b_castle_rights[1])
		fen += "k";
	if (m_b_castle_rights[0])
		fen += "q";
	if (!m_w_castle_rights[1] && !m_w_castle_rights[0] &&
		!m_b_castle_rights[1] && !m_b_castle_rights[0])
		fen += '-';
	fen += ' ';
	// add en passant
	bool can_en_passant = false;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].m_can_en_passant == true &&
			(*this)[i].m_en_passant_move == move_count)
		{
			fen += ('a' + i % 8);
			fen += (char)('0' + 8 - (i / 8));
			can_en_passant = true;
			break;
		}
	}
	if (!can_en_passant)
		fen += "-";
	fen += ' ';
	// 50 move rule
	fen += std::to_string(m_fifty_move_rule) + ' ';
	// move count
	int test = (int(m_parent_game->positions.size() + 2) / 2);
	fen += std::to_string(test);
	return (fen);
}

/// @brief Calculates the set of legal moves for the piece in a given cell
/// @param cell
/// @return a pointer to the first element of an array containing legal move cells
void Tablero::set_possible_moves(Casilla& cell)
{
	cell.m_piece->possible_moves(*this, cell);
}

void Tablero::reset_possible_moves()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla& cell = *m_casilla[i];
		cell.m_posible_destination = false;
	}
}

/// @brief Gets the x,y position of the board (0,0) is upper left
/// 		Expects correct input
/// @param x The absolute x coordinate, equivalent to letters on real board
/// @param y The absolute y coordinate, equivalent to numbers on real board
/// @return The cell on the (x,y) coordinate
Casilla& Tablero::get_cell(const int x, const int y)
{
	const int size = 8;
	// out of borders
	if (x < 0 || x >= size || y < 0 || y >= size)
	{
		static Casilla invalid(*this, s_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x + 8 * y]);
}

/// @brief Gets the cell int the A,N position,(0,0) = a8. (7,7) = a1
/// @param c the column
/// @param y the row
/// @return The (c,y) position on the board (Looking as white pieces)
Casilla& Tablero::get_cell(const char c, const int y)
{
	const int size = 8;
	// out of borders
	if (c < 'a' ||
		c > 'h' ||
		y <= 0 ||
		y > size)
	{
		static Casilla invalid(*this, s_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[(c - 'a') + 8 * (size - y)]);
}

/// @brief Gets the x position cell, counting row by row from upper left
///			Expects valid input
/// @param x The positio on the board
/// @return the cell in the x position
Casilla& Tablero::get_cell(const int x)
{
	// 0 is upper left corner, 63 is opposite one.
	// out of borders
	if (x < 0 || x > 63)
	{
		static Casilla invalid(*this, s_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x]);
}

/// @brief Gets the cell int the x,y position to the self cell
/// @param self The local cell
/// @param relative_x the x relative position from self
/// @param relative_y the y relative position from self
/// @return
Casilla& Tablero::get_cell(Casilla& self, const int relative_x, const int relative_y)
{
	const int size = 8;
	int id = self.m_id;
	// out of borders
	if (id % size + relative_x < 0 ||
		id % size + relative_x >= size ||
		id / size < relative_y ||
		id / size - relative_y >= size)
	{
		return (self);
	}
	return (*m_casilla[id + relative_x - size * relative_y]);
}

/// @brief Checks if a cell is a valid destination for a move
/// @param cell
/// @return 1 if cell is a valid destination
bool Tablero::can_Move_To(Casilla& dst, Casilla& src)
{
	if (is_empty(dst) || dst.getColor() != src.getColor())
		return true;
	return false;
}

/// @return 1 if dst is empty 0 otherwise
bool Tablero::is_empty(Casilla& dst)
{
	return (dst.getFigura() == figura::Vacio ? 1 : 0);
}

int Tablero::can_castle(color c)
{
	if (c == Blanco)
	{
		if (m_w_castle_rights[0] && m_w_castle_rights[1])
			return 2;
		if (m_w_castle_rights[0])
			return 0;
		if (m_w_castle_rights[1])
			return 1;
		return -1;
	}
	if (m_b_castle_rights[0] && m_b_castle_rights[1])
		return 2;
	if (m_b_castle_rights[0])
		return 0;
	if (m_b_castle_rights[1])
		return 1;
	return -1;
}

bool Tablero::hasMoves(color c)
{
	Tablero& T = (*this->m_parent_game->T);
	bool has_moves = false;
	vector<int> v = c == Blanco ? m_w_pieces : m_b_pieces;
	for (auto piece : v)
	{
		if (T.get_cell(piece).getMoveList().size() > 0)
		{
			has_moves = true;
			break;
		}
	}
	return has_moves;
}

/// @brief Performs a move in the board, by swaping the cells if the target is empty,
/// or deleting the origin and creating a new empty. Increment the move count by 1.
/// @param from Id of the origin cell to move
/// @param to Id of the target cell to move
int Tablero::do_move(int from, int to, bool calculating)
{
	if (m_event == Jaque_Mate || m_event == Tablas || m_event == Bandera)
		return m_event; // si acabó, no mueve
	int event = None;
	Tablero& T = (*this);
	T.move_count++;
	// Al paso
	//  condiciones de movimiento
	int lim1, lim2, offset;
	if (turn == Blanco)
		lim1 = 32, lim2 = 40, offset = 8;
	else
		lim1 = 24, lim2 = 32, offset = -8;
	if (T[from].getFigura() == Peon && (to >= lim1 && to < lim2) &&
		(from >= lim1 + 2 * offset && from < lim2 + 2 * offset))
	{
		// si hay peones a derecha o izquierda permitimos flag de tomar al paso.
		Casilla& c_minus = T.get_cell(T[to], -1, 0);
		if (c_minus != T[to] && c_minus.getFigura() == Peon && c_minus.getColor() != T[to].getColor())
			T[to + offset].setEnPassant(true), T[to + offset].setEnPassant_move(T.move_count);
		Casilla& c_plus = T.get_cell(T[to], 1, 0);
		if (c_plus != T[to] && c_plus.getFigura() == Peon && c_plus.getColor() != T[to].getColor())
			T[to + offset].setEnPassant(true), T[to + offset].setEnPassant_move(T.move_count);
	}
	// Enroque
	//  si movemos una torre no podemos enrocar a ese lado
	//  si movemos el rey no podemos enrocar
	// si nos comen una torre no podemos por ese lado !!
	if (from == 0 || to == 0)
		m_b_castle_rights[0] = false;
	if (from == 7 || to == 7)
		m_b_castle_rights[1] = false;
	if (from == 4 || to == 4)
		m_b_castle_rights[0] = false, m_b_castle_rights[1] = false;
	if (from == 56 || to == 56)
		m_w_castle_rights[0] = false;
	if (from == 63 || to == 63)
		m_w_castle_rights[1] = false;
	if (from == 60 || to == 60)
		m_w_castle_rights[0] = false, m_w_castle_rights[1] = false;

	// update 50 move rule
	// si no hay captura o movimiento de peon se incrementa
	if (T[from].m_figure != Peon && T[to].m_figure == Vacio)
		m_fifty_move_rule++;
	// Casilla destino = origen y limpio origen
	T[to] = T[from];
	T[from].clear();
	// en caso de que sea tomar al paso hay que limpiar también el peón que me como
	if (T[to].m_figure == Peon && T[to].m_en_passant_move == move_count - 1) // si el movimiento fue tomar al paso
		T[to + offset].clear();
	// en caso de enroque mover también la torre
	if (from == 60 && to == 62)
	{
		T[to - 1] = T[to + 1];
		T[to + 1].clear();
	}
	else if (from == 60 && to == 58)
	{
		T[to + 1] = T[to - 2];
		T[to - 2].clear();
	}
	else if (from == 4 && to == 6)
	{
		T[to - 1] = T[to + 1];
		T[to + 1].clear();
	}
	else if (from == 4 && to == 2)
	{
		T[to + 1] = T[to - 2];
		T[to - 2].clear();
	}

	// Coronación
	// si un peon llega a la ultima fila promociona
	if (((to >= 0 && to < 8) || (to >= 56 && to < 64)) && T[to].m_figure == Peon)
	{
		T[to].m_figure = m_promocion;
		T[to].m_piece = m_coronacion;
		T[to].setSymbol();
	}

	m_w_pieces.clear();
	m_b_pieces.clear();
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].getColor() == Blanco)
			m_w_pieces.push_back(i);
		else if ((*this)[i].getColor() == Negro)
			m_b_pieces.push_back(i);
	}
	// Añadir a las posiciones de Partida
	// update color pieces list
	if (!calculating)
	{
		m_parent_game->add_pos();
		// Comenzar el otro reloj
		color oponent_color = turn == Blanco ? Negro : Blanco;
		m_parent_game->startColorClock(oponent_color);
		// Comprobación de tiempo
		if (m_parent_game->getColorClock(turn) == 0)
		{
			vector<int>& op_pieces = oponent_color == Blanco ? m_w_pieces : m_b_pieces;
			if (op_pieces.size() > 2)
			{
				m_event = Bandera;
				return Bandera;
			} // suficiente para mate
			if (op_pieces.size() == 1)
			{
				m_event = Tablas;
				return Tablas;
			} // solo rey = tablas
			bool has_mate_poss = false;
			for (auto a : op_pieces)
			{
				if (T[a].m_figure == Reina || T[a].m_figure == Torre ||
					T[a].m_figure == Peon)
					has_mate_poss = true;
			}
			if (!has_mate_poss)
			{
				m_event = Tablas;
				return Tablas;
			} // material insuficiente
			if (has_mate_poss)
			{
				m_event = Bandera;
				return Bandera;
			} // Pierdes
		}
		// actualizar turno
		turn = turn == Blanco ? Negro : Blanco;
		// ver si se da el evento de jaque, jaque mate o tablas
		bool can_move = hasMoves(turn);
		for (auto piece : turn == Blanco ? m_w_pieces : m_b_pieces)
		{
			if (T[piece].m_figure == Rey && T[piece].getCheck(T[piece].m_color))
			{
				event = Jaque;
				/// check mate
				if (!can_move)
					event = Jaque_Mate;
			}
		}
		if (!can_move && event == None)
			event = Tablas;
		if (m_fifty_move_rule == 100 && event == None)
			event = Tablas;
		// comprobar triple repetición
		if (isThreeFold())
			event = Tablas;
	}
	m_event = event;
	return event;
}

/// @brief Prints a list of the possible moves of all the pieces, both colors
void Tablero::print_all_moves()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].m_figure == Vacio)
			continue;
		if ((*this)[i].m_color != turn)
			continue;
		vector<int>& Move_tem = (*this)[i].getMoveList();
		if (Move_tem.size())
			cout << i << "//	";
		for (auto a : Move_tem)
			cout << a << ", ";
		if (Move_tem.size())
			cout << "\n";
	}
}

/// @brief gets the number of possible moves of the turn
int Tablero::count_possible_moves()
{
	vector<int> pieces = turn == Blanco ? m_w_pieces : m_b_pieces;
	int m_count = 0;
	for (auto a : pieces)
	{
		m_count += (*this)[a].getMoveList().size();
	}
	return (m_count);
}

void Tablero::print_checks(color c)
{
	cout << endl;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i > 0 && i % 8 == 0)
			cout << endl;
		cout << (*this)[i].getCheck(c);
	}
	cout << endl;
}

/// @brief Sets the figure the pawn will be converted to on promotion
void Tablero::setCoronacion(figura f)
{
	m_promocion = f;
	switch (f)
	{
	case Peon:
	case Rey:
	case Reina:
		m_coronacion = static_cast<Rook*>(s_queen);
		break;
	case Torre:
		m_coronacion = s_rook;
		break;
	case Alfil:
		m_coronacion = s_bishop;
		break;
	case Caballo:
		m_coronacion = s_knight;
		break;
	default:
		m_coronacion = static_cast<Rook*>(s_queen);
		break;
	}
}

bool Tablero::isThreeFold()
{
	const vector<FEN>& v = m_parent_game->positions;
	string a, b;
	for (int i = 0; i < (int)v.size() - 2; i++) // cada elemento
	{
		int rep_count = 0;
		for (int j = i + 1; j < (int)v.size(); j++) // emparejo con el resto
		{
			int white_count = 0;
			a = v.at((unsigned long)i);
			b = v.at((unsigned long)j);
			for (int x = 0; x < (int)v.at((unsigned long)i).length() - 1; x++) // comparo si la posicion es igual
			{
				if (v.at((unsigned long)i)[(unsigned long)x] != v.at((unsigned long)j)[(unsigned long)x])
					break;
				if (v.at((unsigned long)i)[(unsigned long)x] == ' ')
					white_count++;
				if (white_count == 4)
					break;
			}
			if (white_count == 4)
				rep_count++;
			if (rep_count == 2)
				return true;
		}
	}
	return false;
}

vector<int> Tablero::get_pseudo_moves(Casilla cell) { return ((cell).getPiece().pseudo_legal(*(this), cell)); }
vector<int> Tablero::get_pseudo_moves(int cell) { return this->get_pseudo_moves(this->get_cell(cell)); }
void Tablero::inicializar() {
	s_king = new King();
	s_queen = new Queen();
	s_rook = new Rook();
	s_knight = new Knight();
	s_bishop = new Bishop();
	s_pawn = new Pawn();
	s_empty = new Empty();
}
