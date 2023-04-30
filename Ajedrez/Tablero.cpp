#include "Tablero.h"
#include "Casilla.h"
#include "Pieza.h"
#include <algorithm>

/// @brief Reads a FEN position for the board initial position
/// @param fen the FEN value, should contain position  and turn only, no castling rights etc..
/// FEN @link ://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
/// @todo check if fen is correct read extra informatios as castling rights etc..
Tablero::Tablero(string fen)
{	
	int		cell = 0;
	bool	all_pos = false; //flag to check if FEN is complete

	//One object per piece type
	m_king = new King();
	m_queen = new Queen();
	m_rook = new Rook();
	m_knight = new Knight();
	m_bishop = new Bishop();
	m_pawn = new Pawn();
	m_empty = new Empty();
	m_initial_board = fen;
	//Read the FEN
	for(char c:fen)
	{
		//Non-Piece FEN characters
		if (c == 'w') {turn = color::Blanco; break;}
		if (all_pos && c == 'b') {turn = color::Negro; break;}
		if (c == '/') {continue;}
		if (c == ' ') {all_pos = true;continue;}
		if (c >= '1' && c <= '8')
		{
			//we have c as char, (c - '0') = c as int
			for (int i = 0; i < (c - '0'); i++) 
			{
				m_casilla[cell] = new Casilla(*this, m_empty, Vacio, noColor, cell);
				cell++;
			}
			continue;
		}
		// minuscula es negro
		color col = c >= 'a' ? Negro : Blanco;
		//Set pieces
		switch (c)
		{
		//black
		case 'R':
		case 'r':
			m_casilla[cell] = new Casilla(*this, m_rook, Torre, col, cell);
			break;
		case 'N':
		case 'n':
			m_casilla[cell] = new Casilla(*this, m_knight, Caballo, col, cell);
			break;
		case 'B':
		case 'b':
			m_casilla[cell] = new Casilla(*this, m_bishop, Alfil, col, cell);
			break;
		case 'Q':
		case 'q':
			m_casilla[cell] = new Casilla(*this, static_cast<Rook*>(m_queen), Reina, col, cell);
			break;
		case 'K':
		case 'k':
			m_casilla[cell] = new Casilla(*this, m_king, Rey, col, cell);
			break;
		case 'P':
		case 'p':
			m_casilla[cell] = new Casilla(*this, m_pawn, Peon, col, cell);
			break;
		default:
			break;
		}
		cell++;
	}
	//List of pieces of each colors
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].getColor() == Blanco) m_w_pieces.push_back(i);
		else if ((*this)[i].getColor() == Negro) m_b_pieces.push_back(i);
	}
}

/// @brief Libera la memoria reservada para la clase @ref Tablero
Tablero::~Tablero()
{
}
/// @brief Prints a console representation of the board
void	Tablero::print ()
{
	const int UnicodeVal= 9812;
	const int NumOfPieces= 6;

	setlocale(LC_ALL, "en_US.UTF-8");
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		int pieceVal = int(cell.m_figure);
		int colorVal = int(cell.m_color);
		pieceVal = colorVal == 1 ? pieceVal + NumOfPieces : pieceVal; // blanco o negro
		pieceVal = pieceVal == 0 ? (-UnicodeVal + ' ') : pieceVal - 1; // si está vacio -> espacio
		wprintf(L"%lc", UnicodeVal + pieceVal);
		if(!((i + 1) % 8)) cout << endl; 
	}
	cout << endl << "Turno de " << (turn == Blanco ? "Blancas" : "Negras") << endl << "========"<< endl;
}
/// @brief Prints a console representation of the possible moves of the @ref Piece contained on cell
void	Tablero::printPosibleMoves (Casilla &cell)
{
	int cell_count = 0;

	set_possible_moves(cell);
	setlocale(LC_ALL, "en_US.UTF-8");
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &c = *m_casilla[i];
		int pieceVal;
		bool b = c.m_posible_destination;
		pieceVal = b ? 'x' : ' '; // si es posible moverse marca
		wprintf(L"%lc", '0' + b);
		if(!(++cell_count % 8)) cout << endl; 
	}
	cout << endl;
	this->reset_possible_moves();
}
/// @brief Gets the FEN code of the current board state
/// @return FEN code as string
/// FEN: @link https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
string Tablero::get_fen()
{
	string	fen = "";
	bool	empty = false;
	int		empty_count = 0;
	int		cell_count = 0;

	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		//empty cell management
		empty = is_empty(cell);//cell.getFigure() == figura::Vacio ? true : false;
		if (empty) empty_count++;
		if (!empty && empty_count) fen += '0' + empty_count,empty_count = 0;
		//cell with piece
		if (!empty) fen += cell.getSymbol();
		//end of board row management
		if (!(++cell_count % ROW_SIZE))
		{
			if (empty_count)
			{
				fen += '0' + empty_count;
				empty = false;
				empty_count = 0;
			}
			if (cell_count < BOARD_SIZE) fen += '/';
		}
	}
	//add turn
	fen += turn==Blanco ? " w" : " b";
	return (fen);
}

/// @brief Calculates the set of legal moves for the piece in a given cell
/// @param cell 
/// @return a pointer to the first element of an array containing legal move cells
void Tablero::set_possible_moves(Casilla &cell)
{
	cell.m_piece->possible_moves(*this, cell);
}

void Tablero::reset_possible_moves()
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		cell.m_posible_destination = false;
	}
}

/// @brief Gets the x,y position of the board (0,0) is upper left
/// 		Expects correct input
/// @param x The absolute x coordinate, equivalent to letters on real board
/// @param y The absolute y coordinate, equivalent to numbers on real board
/// @return The cell on the (x,y) coordinate
Casilla	&Tablero::get_cell(const int x, const int y)
{
	const	int size = 8;
	//out of borders
	if(x < 0 || x >= size || y < 0 || y >= size )
	{
		static Casilla	invalid(*this, m_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x + 8 * y]);
}

/// @brief Gets the cell int the A,N position,(0,0) = a8. (7,7) = a1
/// @param c the column
/// @param y the row
/// @return The (c,y) position on the board (Looking as white pieces)
Casilla	&Tablero::get_cell(const char c, const int y)
{
	const	int size = 8;
	//out of borders
	if (c < 'a' ||
		c > 'h' ||
		y <= 0 ||
		y > size )
	{
		static Casilla	invalid(*this, m_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[(c - 'a') + 8 * ( size - y)]);
}

/// @brief Gets the x position cell, counting row by row from upper left
///			Expects valid input
/// @param x The positio on the board 
/// @return the cell in the x position
Casilla	&Tablero::get_cell(const int x)
{
	// 0 is upper left corner, 63 is opposite one.
	//out of borders
	if (x < 0 || x > 63)
	{
		static Casilla	invalid(*this, m_empty, Vacio, noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x]);
}

/// @brief Gets the cell int the x,y position to the self cell
/// @param self The local cell
/// @param relative_x the x relative position from self
/// @param relative_y the y relative position from self
/// @return 
Casilla &Tablero::get_cell(Casilla &self, const int relative_x, const int relative_y)
{
	const	int size = 8;
	int id = self.m_id;
	//out of borders
	if (id % size + relative_x < 0 ||
	 	id % size + relative_x >= size ||
		id / size < relative_y ||
		id / size - relative_y >= size)
	{
		return (self);
	}
	return (*m_casilla[id +  relative_x - size * relative_y]);
}

/// @brief Checks if a cell is a valid destination for a move
/// @param cell 
/// @return 1 if cell is a valid destination
bool Tablero::can_Move_To(Casilla &dst, Casilla &src)
{
	if (is_empty(dst) || dst.getColor() != src.getColor()) 
		return true;
	return false;
}

/// @return 1 if dst is empty 0 otherwise
bool Tablero::is_empty(Casilla &dst)
{
	return (dst.getFigura() == figura::Vacio ? 1 : 0);
}

///@return 1 if dst contains oponents piece, 0 otherwise
bool Tablero::is_enemy_piece(Casilla &dst, color myColor)
{
	if (!is_empty(dst))
		return (dst.getColor() != myColor ? 1 : 0);
	return false;
}

/// @return true if dst is held by opponent's pieces
bool Tablero::is_move_wall(Casilla &dst, Casilla &src)
{
	if(dst.getColor() != color::noColor) return true;
	return false;
}

int Tablero::can_castle(color c) 
{
	if (c == Blanco)
	{
		if(m_w_castle_rights[0] && m_w_castle_rights[1]) return 2;
		if(m_w_castle_rights[0]) return 0;
		if(m_w_castle_rights[1]) return 1;
		return -1;
	}
	if(m_b_castle_rights[0] && m_b_castle_rights[1]) return 2;
	if(m_b_castle_rights[0]) return 0;
	if(m_b_castle_rights[1]) return 1;
	return -1;
}

/// @brief Performs a move in the board, by swaping the cells if the target is empty,
/// or deleting the origin and creating a new empty. Increment the move count by 1.
/// @param from Id of the origin cell to move
/// @param to Id of the target cell to move
void Tablero::do_move(int from, int to)
{
	Tablero &T = (*this);
	T.move_count++;
	//Al paso
	// condiciones de movimiento
	int lim1, lim2, offset;
	if (turn == Blanco) lim1 = 32, lim2 = 40, offset = 8;
	else lim1 = 24, lim2 = 32, offset = -8;
	if (T[from].getFigura() == Peon && (to >= lim1 && to < lim2) && 
		(from >= lim1 + 2 * offset && from < lim2 + 2 * offset))
	{
		//si hay peones a derecha o izquierda permitimos flag de tomar al paso.
		Casilla &c_minus = T.get_cell(T[to],-1,0);
		if (c_minus != T[to] && c_minus.getFigura() == Peon && c_minus.getColor() != T[to].getColor())
			T[to + offset].setEnPassant(true), T[to + offset].setEnPassant_move(T.move_count);
		Casilla &c_plus = T.get_cell(T[to],1,0);
		if (c_plus != T[to] && c_plus.getFigura() == Peon && c_plus.getColor() != T[to].getColor())
			T[to + offset].setEnPassant(true), T[to + offset].setEnPassant_move(T.move_count);
	}
	//Enroque
	// si movemos una torre no podemos enrocar a ese lado
	// si movemos el rey no podemos enrocar
	//si nos comen una torre no podemos por ese lado !!
	if (from == 0 || to == 0) m_b_castle_rights[0] = false;
	if (from == 7 || to == 7) m_b_castle_rights[1] = false;
	if (from == 4 || to == 4) m_b_castle_rights[0] = false,m_b_castle_rights[1] = false;
	if (from == 56 || to == 56) m_w_castle_rights[0] = false;
	if (from == 63 || to == 63) m_w_castle_rights[1] = false;
	if (from == 60 || to == 60) m_w_castle_rights[0] = false,m_w_castle_rights[1] = false;

	//Casilla destino = origen y limpio origen
	T[to] = T[from];
	T[from].clear();
	// en caso de que sea tomar al paso hay que limpiar también el peón que me como
	if (T[to].m_en_passant_move == move_count - 1) //si el movimiento fue tomar al paso
		T[to + offset].clear();
	turn = turn == Blanco ? Negro : Blanco;
	//update color pieces list
	m_w_pieces.clear();
	m_b_pieces.clear();
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].getColor() == Blanco) m_w_pieces.push_back(i);
		else if ((*this)[i].getColor() == Negro) m_b_pieces.push_back(i);
	}
}

/// @brief Prints a list of the possible moves of all the pieces, both colors
void Tablero::print_all_moves()
{
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if ((*this)[i].getMoveList().size())
			cout << i << "//	";
		for(auto a: (*this)[i].getMoveList()) 
		{
			cout << a << ", ";
		}
		if ((*this)[i].getMoveList().size())
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
		 if (i > 0 && i % 8 == 0) cout << endl;
		 cout << (*this)[i].getCheck(c);
	}
	cout << endl;
	(*this).reset_possible_moves();
}
