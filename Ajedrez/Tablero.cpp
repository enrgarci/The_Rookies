/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 18:47:38
 //  Description:
 //
#include "Tablero.h"
#include "Casilla.cpp"

/// @brief Reads a FEN position for the board initial position
/// @param fen the FEN value, should contain position  and turn only, no castling rights etc..
/// @todo check if fen is correct read extra informatios as castling rights etc..
Tablero::Tablero(string fen)
{	
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
				this->m_casilla[cell].setPiece(Pieza::figura::Vacio);
				this->m_casilla[cell].setColor(Pieza::color::noColor);
				cell++;
			}
			continue;
		}
		switch (c)
		{
		//black
		case 'r':
			this->m_casilla[cell].setPiece(Pieza::figura::Torre);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'n':
			this->m_casilla[cell].setPiece(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'b':
			this->m_casilla[cell].setPiece(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'q':
			this->m_casilla[cell].setPiece(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'k':
			this->m_casilla[cell].setPiece(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		case 'p':
			this->m_casilla[cell].setPiece(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Negro);
			break;
		//white
		case 'R':
			this->m_casilla[cell].setPiece(Pieza::figura::Torre);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'N':
			this->m_casilla[cell].setPiece(Pieza::figura::Caballo);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'B':
			this->m_casilla[cell].setPiece(Pieza::figura::Alfil);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'Q':
			this->m_casilla[cell].setPiece(Pieza::figura::Reina);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'K':
			this->m_casilla[cell].setPiece(Pieza::figura::Rey);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		case 'P':
			this->m_casilla[cell].setPiece(Pieza::figura::Peon);
			this->m_casilla[cell].setColor(Pieza::color::Blanco);
			break;
		default:
			break;
		}
		cell++;
	}
}

void	Tablero::print ()
{
	for(auto casilla: m_casilla) 
		cout << int(casilla.getPiece());
}
