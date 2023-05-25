#include "AI.h"
#include "Tablero.h"
#include "ETSIDI.h"
#include "stdlib.h"
#include "Casilla.h"
#include "Pieza.h"

using namespace std;

//the AI makes a move randomly, selecting one of its available pieces only if that piece has moves that it can perform, then moves from its initial square to one selectect from its posible moves at random
int AI::randommove(Tablero& T, color col)
{
	int selectpiece=-1, numpiece, canmove=0, soundmove=0;
	color piece_color;
	vector<int> ia_list_pieces, ia_move_list, enemy_list_pieces;
	int ia_move_size, destinationelement, ia_piece_type, enemy_piece_type;
	ia_list_pieces = T.get_Color_Pieces(col);
	enemy_list_pieces = T.get_Color_Pieces(Blanco);
	numpiece = ia_list_pieces.size();
	for (int i = 0; i < numpiece; i++)
	{
		ia_move_list = T[ia_list_pieces[i]].getMoveList();
		if (ia_move_list.size() != 0)
		{
			canmove = 1;
			break;
		}
	} //if l38, hacer que actualice la pieza mas valiosa que puede comer y solo coma si es mas valiosa que ella destino getfigura tiene que ser menor o igual que origen get figura
	if (canmove == 1)
	{
		for (int piece = 0; piece < numpiece; piece++)
		{
			ia_move_list = T[ia_list_pieces[piece]].getMoveList();
			ia_piece_type = T[ia_list_pieces[piece]].getFigura();
			for (int move = 0; move < ia_move_list.size(); move++)
			{
				for (int white_p = 0; white_p < enemy_list_pieces.size(); white_p++)
				{
					enemy_piece_type = T[enemy_list_pieces[white_p]].getFigura();
					if (ia_move_list[move] == enemy_list_pieces[white_p] && ia_piece_type >= enemy_piece_type)
					{
						selectpiece = ia_list_pieces[piece];
						destinationelement = move;
					}
				}
			}
		}
		if (selectpiece == -1)
		{
			do
			{
				selectpiece = ia_list_pieces[ETSIDI::lanzaDado(numpiece + 1, 1) - 1];
				ia_move_list = T[selectpiece].getMoveList();
				ia_move_size = ia_move_list.size();
			} while (ia_move_size == 0);
			destinationelement = ETSIDI::lanzaDado(ia_move_size + 1, 1) - 1;
			soundmove = T.do_move(selectpiece, ia_move_list[destinationelement]);
		}
		else
		{
			ia_move_list = T[selectpiece].getMoveList();
			soundmove = T.do_move(selectpiece, ia_move_list[destinationelement]);
		}
	}
	else
	{
		cout << "The AI cant move" << endl;
	}
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
	return soundmove;
}
