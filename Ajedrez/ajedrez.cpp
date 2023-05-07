#include "Tablero.h"
#include "Partida.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","",-1,0,"Q7/6K1/8/8/8/2N5/6P1/8 w - - 0 1");
	int c = 56;
	vector<int> A;
	A = (P.T->get_pseudo_moves(56));
	
	for(auto a : A) cout << a << " ";
	P.T->print_checks(Blanco);
	P.T->print_checks(Negro);
	cout << endl <<P.T->get_cell(47).getCheck(Negro);
}
