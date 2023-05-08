#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0);

	P.T->print();
	cout << P.perf(P,2);
	// P.T->print_all_moves();
	// P.T->printPosibleMoves(14);
	// for (int i = 0; i < BOARD_SIZE; i++)
	// {
	// 	if (i % 8 == 0) cout << endl;
	// 	cout << P.T->get_cell(50).isPinned(P.T->get_cell(i));
	// }
	// cout << endl;
	
}
