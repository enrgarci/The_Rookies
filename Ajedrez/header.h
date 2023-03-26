/// Have a nice day !
 //  Author: enrgarci
 //  Create Time: 2023-03-25 16:56:29
 //  Modified by: enrgarci
 //  Modified time: 2023-03-26 17:53:19
 //  Description:
 //

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
