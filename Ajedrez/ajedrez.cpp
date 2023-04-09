#include "Partida.h"
#include "Tablero.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Partida myGame;
	cout << myGame.getPlayer() + "\n";
	Tablero myBoard = myGame.getBoard();
	myBoard.print();
}
