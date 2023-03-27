/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-27 18:14:08
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
	m_initial_board = fen;
	int	cell = 0;
	bool all_pos = false;
	for(char c:fen)
	{
		if (c == 'w') {this->m_mueve = Blanco; break;}
		if (all_pos && c == 'b') {this->m_mueve = Negro; break;}
		if (c == '/') {continue;}
		if (c == ' ') {all_pos = true;continue;}
		if (c >= '1' && c <= '8')
		{
			for (int i = 0; i < (c - '0'); i++)
			{
				this->m_casilla[cell].setFigure(Pieza::figura::Vacio);
				this->m_casilla[cell].setColor(Pieza::color::noColor);
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
			break;
		case 'n':
			this->m_casilla[cell].setFigure(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'b':
			this->m_casilla[cell].setFigure(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'q':
			this->m_casilla[cell].setFigure(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'k':
			this->m_casilla[cell].setFigure(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'p':
			this->m_casilla[cell].setFigure(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		//white
		case 'R':
			this->m_casilla[cell].setFigure(Pieza::figura::Torre);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'N':
			this->m_casilla[cell].setFigure(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'B':
			this->m_casilla[cell].setFigure(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'Q':
			this->m_casilla[cell].setFigure(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'K':
			this->m_casilla[cell].setFigure(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'P':
			this->m_casilla[cell].setFigure(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
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
	for(auto casilla: m_casilla) 
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
