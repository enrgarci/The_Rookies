#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"r7/8/r7/8/k7/8/8/P2K4 w - - 0 1");
	int c = 56;
	vector<int> A;
	A = ((P.T)->get_cell(c).getPiece().pseudo_legal(*(P.T), P.T->get_cell(c)));
	
	for(auto a : A) cout << a << " ";
}
