#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

typedef string FEN;
const int BOARD_SIZE = 64;
const int ROW_SIZE = 8;
const string INITIAL_POS = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
enum	figura { Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon };
enum	color { noColor, Blanco, Negro };
enum	events { None, Jaque, Jaque_Mate, Tablas };
#endif