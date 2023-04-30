#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","r1B1k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1");
	Tablero &T = P.getBoard();
	Casilla C = T[16];


	T.print();
	T.reset_possible_moves();
	T.do_move(63,7);
	T.print();
	T.printPosibleMoves(4);
	T.printPosibleMoves(60);
}
