#include "Tablero.h"
#include "Partida.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida P("","","8/8/8/8/8/8/8/8)");
	Tablero T = P.getBoard();
	(T).print();
}
