#pragma once
#include <vector>
#include "Boton.h"


class Interface
{

	struct coordinate {
		float x, y;
	};
	int gridSize;
	int screen_width;
	int screen_height;
	float board_size;
	float board_origin_x;
	float board_origin_y;
	float square_size;
	bool fullscreen;
	bool doRotate = false;
	int click_flag = 0;
	int cell_number;
	coordinate grid_coordinates[8][8];
	int CorIndex = 0;

	Boton pauseMenu, playBackButton, playForwardButton, playLastButton, playFirstButton;

	//Colors
	float br, bg, bb, wr, wg, wb;



public:
	void init();
	coordinate getGridCoordinate(int col, int row);
	void changeOrigin(int& value);
	void rotateBoard(int value, int& col, int& row);
	void drawBoard(int EstadoSkin);
	void drawPieces(int EstadoSkin);
	void drawPossibleMoves(std::vector<int>& move_list);
	void drawCoronation(int EstadoSkin, int cell, std::vector<int>& move_list); //añadir
	void drawLastMove(int* movement, std::vector<int>& move_list, bool check_list);
	void drawMovement(int EstadoSkin);
	void reshape(int w, int h);
	void mouseBoard(int button, int state, int x, int y, int & Estado);
	void keyboardFullscreen(unsigned char key, int x, int y);

	void drawButtons();
	void mouseButtons(int button, int state, int x, int y, int& Estado);
	void submenu(int& Estado);
	

};
