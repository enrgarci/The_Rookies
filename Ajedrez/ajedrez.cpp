#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","8/k7/8/8/8/8/8/n7");
	Tablero T = P.getBoard();
	Casilla C = T.get_cell(56);
	int n = 0;

	for (int i = 0; i < 100000; i++)
	{
		C.getPiece().possible_moves(T,C);
	}
	cout<<"\n" << n <<"\n";
	for(auto i: C.getMoveList(T)) cout << i << " ";
	T.printPosibleMoves(C);
}
