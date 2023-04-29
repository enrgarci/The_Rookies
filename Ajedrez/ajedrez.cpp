#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","8/k7/R7/8/8/8/8/n7");
	Tablero &T = P.getBoard();
	Casilla C = T[16];

	T.print();
	T.do_move(8,9);
	T.print_all_moves();
	T.print();
	T.do_move(9,10);
	T.do_move(16,56);
	T.do_move(56,57);
	T.print_all_moves();
}
