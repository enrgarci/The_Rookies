#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","K7/8/8/8/8/8/8/R7");
	Tablero T = P.getBoard();
	Casilla C = *T.get_cell(56);

	C.getPiece()->possible_moves(T, C);
	T.print();
	T.printPosibleMoves(*T.get_cell(56));
	T.reset_possible_moves();
	T.printPosibleMoves(*T.get_cell(0));

}
