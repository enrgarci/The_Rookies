/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-28 01:47:50
 //  Description:
 //
#include "Tablero.h"
#include "Casilla.cpp"
#include <stdio.h>

/// @brief Reads a FEN position for the board initial position
/// @param fen the FEN value, should contain position  and turn only, no castling rights etc..
// FEN: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
/// @todo check if fen is correct read extra informatios as castling rights etc..
Tablero::Tablero(string fen)
{	
	int		cell = 0;
	bool	all_pos = false;

	m_initial_board = fen;
	for(char c:fen)
	{
		if (c == 'w') {this->m_mueve = Pieza::Blanco; break;}
		if (all_pos && c == 'b') {this->m_mueve = Pieza::Negro; break;}
		if (c == '/') {continue;}
		if (c == ' ') {all_pos = true;continue;}
		if (c >= '1' && c <= '8')
		{
			for (int i = 0; i < (c - '0'); i++)
			{
				this->m_casilla[cell].setFigure(Pieza::figura::Vacio);
				this->m_casilla[cell].setColor(Pieza::color::noColor);
				this->m_casilla[cell].setId(cell);
				cell++;
			}
			continue;
		}
		switch (c)
		{
		//black
		case 'r':
			this->m_casilla[cell].setFigure(Pieza::figura::Torre);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		case 'n':
			this->m_casilla[cell].setFigure(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		case 'b':
			this->m_casilla[cell].setFigure(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		case 'q':
			this->m_casilla[cell].setFigure(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		case 'k':
			this->m_casilla[cell].setFigure(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		case 'p':
			this->m_casilla[cell].setFigure(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			this->m_casilla[cell].setId(cell);
			break;
		//white
		case 'R':
			this->m_casilla[cell].setFigure(Pieza::figura::Torre);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		case 'N':
			this->m_casilla[cell].setFigure(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		case 'B':
			this->m_casilla[cell].setFigure(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		case 'Q':
			this->m_casilla[cell].setFigure(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		case 'K':
			this->m_casilla[cell].setFigure(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		case 'P':
			this->m_casilla[cell].setFigure(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			this->m_casilla[cell].setId(cell);
			break;
		default:
			break;
		}
		cell++;
	}
}

/// @brief Prints a console representation of the board
void	Tablero::print ()
{
	int cell = 0;
	const int UnicodeVal= 9812;
	const int NumOfPieces= 6;

	setlocale(LC_ALL, "en_US.UTF-8");
	for(Casilla casilla: m_casilla) 
	{
		int pieceVal = int(casilla.getFigure());
		int colorVal = int(casilla.getColor());
		pieceVal = colorVal == 1 ? pieceVal + NumOfPieces : pieceVal; // blanco o negro
		pieceVal = pieceVal == 0 ? (-UnicodeVal + ' ') : pieceVal - 1; // si está vacio -> espacio
		wprintf(L"%lc", UnicodeVal + pieceVal);
		if(!(++cell % 8)) cout << endl; 
	}
	cout << endl << "Turno de " << (!m_mueve ? "Blancas" : "Negras") << endl;
}
/// @brief Prints a console representation of the possible moves of a piece
void	Tablero::printPosibleMoves (Casilla cell)
{
	int cell_count = 0;
	const int UnicodeBox= 2610;
	const int UnicodeXBox= 2612;

	set_possible_moves(cell);
	setlocale(LC_ALL, "en_US.UTF-8");
	for(Casilla casilla: m_casilla) 
	{
		int pieceVal;
		bool b = casilla.getPosMove();
		pieceVal = b ? 'x' : ' '; // si es posible moverse marca
		wprintf(L"%lc", '0' + b);
		if(!(++cell_count % 8)) cout << endl; 
	}
	cout << endl;
}
/// @brief Gets the FEN code of the current board state
/// @return FEN code as string
// FEN: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
string Tablero::get_fen()
{
	string	fen = "";
	char	new_piece;
	bool	empty = false;
	int		empty_count = 0;
	int		cell_count = 0;

	for(Casilla cell: m_casilla)
	{
		//empty cell management
		empty = cell.getFigure() == Pieza::Vacio ? true : false;
		if (empty) empty_count++;
		if (!empty && empty_count) fen += '0' + empty_count,empty_count = 0;
		//cell with piece
		switch (cell.getFigure())
		{
		case Pieza::Rey:
			new_piece = 'K';
			break;
		case Pieza::Reina:
			new_piece = 'Q';
			break;
		case Pieza::Torre:
			new_piece = 'R';
			break;
		case Pieza::Alfil:
			new_piece = 'B';
			break;
		case Pieza::Caballo:
			new_piece = 'N';
			break;
		case Pieza::Peon:
			new_piece = 'P';
			break;
		default:
			break;
		}
		//change to lower if color is black
		if (cell.getColor() == 2) new_piece += ('a' - 'A'); 
		if (!empty) fen += new_piece;
		//end of board row management
		if (!(++cell_count % 8))
		{
			if (empty_count)
			{
				fen += '0' + empty_count;
				empty = false;
				empty_count = 0;
			}
			fen += '/';
		}
	}
	//add turn
	fen += m_mueve ? " w" : " b";
	return (fen);
}

/// @brief Calculates the set of legal moves for the piece in a given cell
/// @param cell 
/// @return a pointer to the first element of an array containing legal move cells
void Tablero::set_possible_moves(Casilla cell)
{
	posible_king(cell);///bypass
	if (!cell.getFigure()) return;
	switch (cell.getFigure())
	{
		case Pieza::Rey:
			posible_king(cell);
			break;
		case Pieza::Reina:
			posible_king(cell);
			break;
		case Pieza::Torre:
			posible_king(cell);
			break;
		case Pieza::Alfil:
			posible_king(cell);
			break;
		case Pieza::Caballo:
			posible_king(cell);
			break;
		case Pieza::Peon:
			posible_king(cell);
			break;
		default:
			break;
	}
}

void Tablero::reset_possible_moves()
{
	for(auto i: m_casilla) i.setPosMove(false);
}

/// @brief Gets the x,y position of the board (0,0) is upper left
/// 		Expects correct input
/// @param x The absolute x coordinate, equivalent to letters on real board
/// @param y The absolute y coordinate, equivalent to numbers on real board
/// @return The cell on the (x,y) coordinate
Casilla	Tablero::get_cell(int x, int y)
{
	const	int size = 8;
	//out of borders
	if(x < 0 || x >= size || y < 0 || y >= size )
	{
		Casilla	invalid;
		invalid.setId(-1);
		return (invalid);
	}
	return (m_casilla[x + 8 * y]);
}

/// @brief Gets the cell int the A,N position,(0,0) = a8. (7,7) = a1
/// @param c the column
/// @param y the row
/// @return The (c,y) position on the board (Looking as white pieces)
Casilla	Tablero::get_cell(char c, int y)
{
	const	int size = 8;
	//out of borders
	if(c < 'a' ||
	 c > 'h' ||
	  y <= 0 ||
	   y > size )
	{
		Casilla	invalid;
		invalid.setId(-1);
		return (invalid);
	}
	return (m_casilla[(c - 'a') + 8 * ( size - y)]);
}

/// @brief Gets the x position cell, counting row by row from upper left
///			Expects valid input
/// @param x The positio on the board 
/// @return the cell in the x position
inline Casilla	Tablero::get_cell(int x)
{
	// 0 is upper left corner, 63 is opposite one.
	//out of borders
	if(x < 0 || x > 63)
	{
		Casilla	invalid;
		invalid.setId(-1);
		return (invalid);
	}
	return (m_casilla[x]);
}

/// @brief Gets the cell int the x,y position to the self cell
/// @param self The local cell
/// @param relative_x the x relative position from self
/// @param relative_y the y relative position from self
/// @return 
Casilla Tablero::get_cell(Casilla self, int relative_x, int relative_y)
{
	const	int size = 8;
	//out of borders
	if(self.getId() % 8 + relative_x < 0 ||
	 	self.getId() % 8 + relative_x >= size ||
		self.getId() / 8 - relative_y < 0 ||
		 self.getId() / 8 - relative_y >= size )
	{
		Casilla	invalid;
		invalid.setId(-1);
		return (invalid);
	}
	return (get_cell(self.getId() +  relative_x - 8 * relative_y));
}

/// @brief Checks if a cell is a valid destination for a move
/// @param cell 
/// @return 1 if cell is a valid destination
bool Tablero::can_Move_To(Casilla dst, Casilla src)
{
	if (dst.getFigure() == Pieza::Vacio || dst.getColor() != src.getColor()) 
		return true;
	return false;
}

/// @brief set True as posible moves the posible king moves from cell
void Tablero::posible_king(Casilla cell)
{	
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			if (!x && !y) continue;
			Casilla relative = get_cell(cell, x, y);
			if(relative.getId() >= 0 && can_Move_To(relative, cell)) /*&& !get_cell(cell, x, y).getCheck()*/
				m_casilla[relative.getId()].setPosMove(true);
		}
	}
}