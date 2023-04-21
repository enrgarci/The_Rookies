#include "Boton.h"
#include <iostream>




void Boton::Draw()
{
	glBegin(GL_POLYGON);
	
	glBegin(GL_QUADS);
	glColor3ub(r, g, b);
	glTexCoord2d(0, 1);     glVertex2f(x, y);
	glTexCoord2d(1, 1);     glVertex2f(x + length, y);
	glTexCoord2d(1, 0);     glVertex2f(x + length, y + height);
	glTexCoord2d(0, 0);     glVertex2f(x, y + height);
	glEnd();

}

void Boton::Set(float x, float y, float length, float height, int r, int g, int b)
{
	float toScreenWidth =(float) 1 / glutGet(GLUT_SCREEN_WIDTH);
	float toScreenHeigth = (float)1 / glutGet(GLUT_SCREEN_HEIGHT);
	float toScreen = toScreenWidth < toScreenHeigth ? toScreenWidth : toScreenHeigth;

	this->x = (float)x*toScreen;
	this->y = (float)y*toScreen;

	this->length = (float)length * toScreen;
	this->height = (float)height * toScreen;

	this->r = r;
	this->g = g;
	this->b = b;
}


bool Boton::isInside(int button,int state,float xMouse,float yMouse) {
	float toScreenWidth = (float)1 / glutGet(GLUT_SCREEN_WIDTH);
	float toScreenHeigth = (float)1 / glutGet(GLUT_SCREEN_HEIGHT);
	float toScreen = toScreenWidth > toScreenHeigth ? toScreenWidth : toScreenHeigth;

	xMouse *= toScreen;
	yMouse = (-yMouse + glutGet(GLUT_SCREEN_HEIGHT)) * toScreen;
	//yMouse *= (- yMouse + glutGet(GLUT_SCREEN_HEIGHT))* toScreen;
	//yMouse *= yMouse * toScreen;

	std::cout << std::endl << x << "<" << xMouse << "<" << x + length << "\t\t";
	std::cout << std::endl << y << "<" << yMouse << "<" << y + height << std::endl;

	if ((x < xMouse && xMouse < x + length) && (y < yMouse && yMouse < y + height))
	{
		std::cout << " DENTRO ";
		return true;
	}
	else
	{
		std::cout << " Fuera ";
		return false;
	}
	
}
