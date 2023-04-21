#pragma once
#include "freeglut.h"
#include "Mouse.h"
#include <iostream>

class Boton
{
private:
	//Position of the bottom-left corner
	float x;
	float y;

	//Area
	float length;
	float height;

	//Color
	int r;
	int g;
	int b;
	bool clickiz;


public: 
	Boton() {};
	Boton(float x, float y, float length, float height, int r, int g, int b ) : x(x), y(y), length(length), height(height), r(r), g(g), b(b) {}

	bool isInside(int button, int state, float xMouse, float yMouse);
	void Draw();
	void Set(float x, float y, float length, float height, int r, int g, int b);
	//bool isInside(int,);
};