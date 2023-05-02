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
	T.printPosibleMoves(60);
	T.print_checks(Blanco);
	T.print_all_moves();
}
