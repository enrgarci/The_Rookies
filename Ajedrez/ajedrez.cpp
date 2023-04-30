#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","");
	Tablero &T = P.getBoard();
	Casilla C = T[16];

	T.print();
	T.do_move(55,39);
	T.print();
	T.do_move(8,24);
	T.print();
	T.do_move(39,31);
	T.print();
	T.do_move(24,32);
	T.print();
	T.do_move(49,33);
	T.print();
	T.do_move(32,41);
	T.print();
	T.do_move(54,46);
	T.print();
	T.do_move(14,30);
	T.print();
	T.do_move(31,22);
	T.print();
	T.printPosibleMoves(30);
}
