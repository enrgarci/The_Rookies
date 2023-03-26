/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-25 16:55:19
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 18:40:25
 //  Description: Primera prueba para la creacción de un juego de ajedrez en c++
 //

#include "Tablero.h"

using namespace std;

int main()
{
	cout << "Hello Chess" << endl;
	Tablero mainT("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
	mainT.print();
}
