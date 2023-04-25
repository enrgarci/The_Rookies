#pragma once
#include <vector>

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
	int click_flag = 0;
	int cell_number;
	coordinate grid_coordinates[8][8];

public:
	void init();
	coordinate getGridCoordinate(int col, int row);
	void changeOrigin(int& value);
	void rotateBoard(int value, int& col, int& row);
	void drawBoard();
	void drawPieces();
	void drawPossibleMoves(std::vector<int>& move_list);
	void drawMovement();
	void reshape(int w, int h);
	void mouseBoard(int button, int state, int x, int y);
	void keyboardFullscreen(unsigned char key, int x, int y);

};

