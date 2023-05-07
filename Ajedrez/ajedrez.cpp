#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"1r6/8/8/8/8/K7/8/R7 w - - 0 1");

	P.T->printPosibleMoves(40);
}
