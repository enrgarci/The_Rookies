#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"rnbqkbnr/pp1pp1pp/8/2p1Pp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6 0 3");

	P.T->print();
	// cout << P.perf(P,4);
	P.T->print_all_moves();
	P.T->printPosibleMoves(28);
	// for (int i = 0; i < BOARD_SIZE; i++)
	// {
	// 	if (i % 8 == 0) cout << endl;
	// 	cout << P.T->get_cell(50).isPinned(P.T->get_cell(i));
	// }
	// cout << endl;
	
}
