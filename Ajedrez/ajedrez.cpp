#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"8/R3r3/8/8/5K2/8/8/6r1 w - - 0 1");

	P.T->print();
	// P.T->print_all_moves();
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		if (i % 8 == 0) cout << endl;
		cout << P.T->get_cell(37).isPinned(P.T->get_cell(i));
	}
	cout << endl;
	
}
