#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

const char W_KING = 'K';
const char B_KING = 'k';

const int BOARD_SIZE = 64;
const int ROW_SIZE = 8;
const string INITIAL_POS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
enum	turno {Blanco, Negro};
enum	figura	{Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon};
enum	color	{noColor, Blanco, Negro};
// class Pieza
// {
// public:
// 	enum	figura	{Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon} fig;
// 	enum	color	{noColor, Blanco, Negro} col;
// };

#endif // HEADER_H
