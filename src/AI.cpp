#include "AI.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include "stdlib.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

//the AI makes a move randomly, selecting one of its available pieces only if that piece has moves that it can perform, then moves from its initial square to one selectect from its posible moves at random
void AI::randommove(Tablero& T, color col)
{
	int selectpiece, numpiece;
	color piece_color;
	vector<int> ia_list_pieces, ia_move_list;
	int ia_move_size, destinationelement;
	ia_list_pieces = T.get_Color_Pieces(col);
	numpiece = ia_list_pieces.size();
	do
	{
		selectpiece = ia_list_pieces[ETSIDI::lanzaDado(numpiece + 1, 1) - 1];
		ia_move_list = T[selectpiece].getMoveList();
		ia_move_size = ia_move_list.size();
	} while (ia_move_size == 0);
	destinationelement = ETSIDI::lanzaDado(ia_move_size + 1, 1) - 1;
	T.do_move(selectpiece, ia_move_list[destinationelement]);

	//cout << selectpiece << endl << ia_move_list[destinationelement] << endl;
	//int inicell;
	/*do
	{
		inicell = ETSIDI::lanzaDado(65, 1) - 1;
		piece_color = T[inicell].getPiece().getColor();
		ia_move_list = T[inicell].getMoveList(T);
		max = ia_move_list.size();
	} while (piece_color != col || max == 0);	*/
	//T.do_move(inicell,ia_move_list[destinationelement]);
}