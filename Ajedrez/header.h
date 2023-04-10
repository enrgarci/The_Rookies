#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

const char W_KING = 'K';
const char B_KING = 'k';
const char W_QUEEN = 'Q';
const char B_QUEEN = 'q';
const char W_ROOK = 'R';
const char B_ROOK = 'r';
const char W_BISHOP = 'B';
const char B_BISHOP = 'b';
const char W_KNIGHT = 'N';
const char B_KNIGHT = 'n';
const char W_PAWN = 'P';
const char B_PAWN = 'p';
const int BOARD_SIZE = 64;
const int ROW_SIZE = 8;
const string INITIAL_POS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
// enum	turno {Blanco, Negro};
enum	figura	{Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon};
enum	color	{noColor, Blanco, Negro};
// class Pieza
// {
// public:
// 	enum	figura	{Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon} fig;
// 	enum	color	{noColor, Blanco, Negro} col;
// };

#endif
