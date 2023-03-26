/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-26 14:12:51
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 18:40:11
 //  Description:
 //
 
#ifndef TABLERO_H
#define TABLERO_H

#include "Casilla.h"

using std::cout;
using std::endl;
using std::string;

enum Turno {Blanco, Negro};

 class Tablero
{
private:
	Casilla m_casilla[64];
	Turno	m_mueve;
public:
	Tablero (string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	void	print();
};

#endif
