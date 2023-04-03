#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class Pieza
{
public:
	enum	figura	{Vacio, Rey, Reina, Torre, Alfil, Caballo, Peon} fig;
	enum	color	{noColor, Blanco, Negro} col;
};

#endif // HEADER_H
