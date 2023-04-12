#include "Tablero.h"
#include "Casilla.h"
#include "Pieza.h"

/// @brief Reads a FEN position for the board initial position
/// @param fen the FEN value, should contain position  and turn only, no castling rights etc..
/// FEN @link ://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
/// @todo check if fen is correct read extra informatios as castling rights etc..
Tablero::Tablero(string fen)
{	
	int		cell = 0;
	bool	all_pos = false;

	m_initial_board = fen;
	for(char c:fen)
	{
		if (c == 'w') {turn = color::Blanco; break;}
		if (all_pos && c == 'b') {turn = color::Negro; break;}
		if (c == '/') {continue;}
		if (c == ' ') {all_pos = true;continue;}
		if (c >= '1' && c <= '8')
		{
			//we have c as char, (c - '0') = c as int
			for (int i = 0; i < (c - '0'); i++) 
			{
				m_casilla[cell] = new Casilla(new Empty(), noColor, cell);
				cell++;
			}
			continue;
		}
		switch (c)
		{
		//black
		case 'r':
			m_casilla[cell] = new Casilla(new Rook(), Negro, cell);
			break;
		case 'n':
			m_casilla[cell] = new Casilla(new Knight(), Negro, cell);
			break;
		case 'b':
			m_casilla[cell] = new Casilla(new Bishop(), Negro, cell);
			break;
		case 'q':
			m_casilla[cell] = new Casilla(static_cast<Rook*>(new Queen()), Negro, cell);
			break;
		case 'k':
			m_casilla[cell] = new Casilla(new King(), Negro, cell);
			break;
		case 'p':
			m_casilla[cell] = new Casilla(new Pawn(), Negro, cell);
			break;
		//white
		case 'R':
			m_casilla[cell] = new Casilla(new Rook(), Blanco, cell);
			break;
		case 'N':
			m_casilla[cell] = new Casilla(new Knight(), Blanco, cell);
			break;
		case 'B':
			m_casilla[cell] = new Casilla(new Bishop(), Blanco, cell);
			break;
		case 'Q':
			m_casilla[cell] = new Casilla(static_cast<Rook*>(new Queen()), Blanco, cell);
			break;
		case 'K':
			m_casilla[cell] = new Casilla(new King(), Blanco, cell);
			break;
		case 'P':
			m_casilla[cell] = new Casilla(new Pawn(), Blanco, cell);
			break;
		default:
			break;
		}
		cell++;
	}
}

/// @brief Libera la memoria reservada para la clase @ref Tablero
Tablero::~Tablero()
{
}
/// @brief Prints a console representation of the board
void	Tablero::print ()
{
	int cell_count = 0;
	const int UnicodeVal= 9812;
	const int NumOfPieces= 6;

	setlocale(LC_ALL, "en_US.UTF-8");
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		int pieceVal = int(cell.getPiece().getFig());
		int colorVal = int(cell.getPiece().getColor());
		pieceVal = colorVal == 1 ? pieceVal + NumOfPieces : pieceVal; // blanco o negro
		pieceVal = pieceVal == 0 ? (-UnicodeVal + ' ') : pieceVal - 1; // si está vacio -> espacio
		wprintf(L"%lc", UnicodeVal + pieceVal);
		if(!(++cell_count % 8)) cout << endl; 
	}
	cout << endl << "Turno de " << (turn ? "Blancas" : "Negras") << endl;
}
/// @brief Prints a console representation of the possible moves of the @ref Piece contained on cell
void	Tablero::printPosibleMoves (Casilla &cell)
{
	int cell_count = 0;
	const int UnicodeBox= 2610;
	const int UnicodeXBox= 2612;

	set_possible_moves(cell);
	setlocale(LC_ALL, "en_US.UTF-8");
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		int pieceVal;
		bool b = cell.getPosMove();
		pieceVal = b ? 'x' : ' '; // si es posible moverse marca
		wprintf(L"%lc", '0' + b);
		if(!(++cell_count % 8)) cout << endl; 
	}
	cout << endl;
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
		if (!empty) fen += (cell.getPiece()).getSymbol();
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
	(cell.getPiece()).possible_moves(*this, cell);
}

void Tablero::reset_possible_moves()
{
	for(int i = 0; i < BOARD_SIZE; i++)
	{
		Casilla &cell = *m_casilla[i];
		cell.setPosMove(false);
	}
}

/// @brief Gets the x,y position of the board (0,0) is upper left
/// 		Expects correct input
/// @param x The absolute x coordinate, equivalent to letters on real board
/// @param y The absolute y coordinate, equivalent to numbers on real board
/// @return The cell on the (x,y) coordinate
Casilla	&Tablero::get_cell(int x, int y)
{
	const	int size = 8;
	//out of borders
	if(x < 0 || x >= size || y < 0 || y >= size )
	{
		static Casilla	invalid(new Empty(), noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x + 8 * y]);
}

/// @brief Gets the cell int the A,N position,(0,0) = a8. (7,7) = a1
/// @param c the column
/// @param y the row
/// @return The (c,y) position on the board (Looking as white pieces)
Casilla	&Tablero::get_cell(char c, int y)
{
	const	int size = 8;
	//out of borders
	if(c < 'a' ||
	 c > 'h' ||
	  y <= 0 ||
	   y > size )
	{
		static Casilla	invalid(new Empty(), noColor, -1);
		return (invalid);
	}
	return (*m_casilla[(c - 'a') + 8 * ( size - y)]);
}

/// @brief Gets the x position cell, counting row by row from upper left
///			Expects valid input
/// @param x The positio on the board 
/// @return the cell in the x position
Casilla	&Tablero::get_cell(int x)
{
	// 0 is upper left corner, 63 is opposite one.
	//out of borders
	if (x < 0 || x > 63)
	{
		static Casilla	invalid(new Empty(), noColor, -1);
		return (invalid);
	}
	return (*m_casilla[x]);
}

/// @brief Gets the cell int the x,y position to the self cell
/// @param self The local cell
/// @param relative_x the x relative position from self
/// @param relative_y the y relative position from self
/// @return 
Casilla &Tablero::get_cell(Casilla &self, int relative_x, int relative_y)
{
	const	int size = 8;
	int id = self.getId();
	//out of borders
	if(id % size + relative_x < 0 ||
	 	id % size + relative_x >= size ||
		id / size - relative_y < 0 ||
		id / size - relative_y >= size )
	{
		static Casilla	invalid(new Empty(), noColor, -1);
		return (invalid);
	}
	return (get_cell(id +  relative_x - size * relative_y));
}

/// @brief Checks if a cell is a valid destination for a move
/// @param cell 
/// @return 1 if cell is a valid destination
bool Tablero::can_Move_To(Casilla &dst, Casilla &src)
{
	if (is_empty(dst) || (dst.getPiece()).getColor() != (src.getPiece()).getColor()) 
		return true;
	return false;
}

/// @return 1 if dst is empty 0 otherwise
bool Tablero::is_empty(Casilla &dst)
{
	return ((dst.getPiece()).getFig() == figura::Vacio ? 1 : 0);
}

///@return 1 if dst contains oponents piece, 0 otherwise
bool Tablero::is_enemy_piece(Casilla &dst, color myColor)
{
	if (!is_empty(dst))
		return ((dst.getPiece()).getColor() != myColor ? 1 : 0);
	return false;
}

/// @return true if dst is held by opponent's pieces
bool Tablero::is_move_wall(Casilla &dst, Casilla &src)
{
	if((dst.getPiece()).getColor() != color::noColor) return true;
	return false;
}

bool Tablero::can_castle(color c) { return c == Blanco ? m_w_castle_rights : m_b_castle_rights;}
/// @brief Sets m_castle_rights of c player to state
/// @param state 
/// @param c The color of the player to set the state of castle rights
void Tablero::set_castle(bool state, color c) {c == Blanco ? m_w_castle_rights
															: m_b_castle_rights = state;}
/// @brief sets playing side castle right to the oposite state
void Tablero::set_castle() {turn == Blanco ? m_w_castle_rights = !m_w_castle_rights
											: m_b_castle_rights = !m_b_castle_rights;}
