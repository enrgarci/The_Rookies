#include "AI.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include "stdlib.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

//the AI makes a move randomly, selecting one of its available pieces only if that piece has moves that it can perform, then moves from its initial square to one selectect from its posible moves at random
void AI::randommove(Tablero &T)
{
		int inicell;
		color piece_color;
		vector<int> ia_move_list;
		int max, destinationelement;
		do
		{
			inicell = ETSIDI::lanzaDado(64, 1);
			piece_color = T[inicell].getPiece().getColor();
			ia_move_list = T[inicell].getMoveList(T);
			max = ia_move_list.size();
		} while (piece_color != Negro || max == 0);
		destinationelement = ETSIDI::lanzaDado(max+1, 1) - 1;
		T.do_move(inicell,ia_move_list[destinationelement]);
}