#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");

	// P.T->print();
	// P.T->do_move(52,36);
	// P.T->printPosibleMoves(37);
	// P.T->print();
	// P.T->print();
	// P.T->do_move(12,20);
	// P.T->print();
	// P.T->do_move(54,38);
	// P.T->print();
	// cout << " " << P.T->do_move(3,39) << "adasd";
	// P.T->print_all_moves();
	// P.T->print();
	cout << P.perf(P,2);
	// for (int i = 0; i < BOARD_SIZE; i++)
	// {
	// 	if (i % 8 == 0) cout << endl;
	// 	cout << P.T->get_cell(50).isPinned(P.T->get_cell(i));
	// }
	// cout << endl;
	
}
