#include "Tablero.h"
#include "Partida.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","");
	Tablero T = P.getBoard();
	(T).print();
}
