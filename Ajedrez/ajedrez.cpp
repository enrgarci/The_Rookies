#include "Tablero.h"
#include "Partida.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","8/8/8/2p5/8/8/8/8");
	Tablero T = P.getBoard();
	Casilla C = *T.get_cell(26);

	C.getPiece()->possible_moves(T, C);
	T.print();
	T.printPosibleMoves(*T.get_cell(26));

}
