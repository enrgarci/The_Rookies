#pragma once
class Interface
{

	struct coordinate {
		float x, y;
	};
	int gridSize;
	int screen_width;
	int screen_height;
	float board_size;
	float board_origin_x;	//X coordinate of the bottom left corner of the board grid
	float board_origin_y;	//Y coordinate of the bottom left ccorner of the board grid
	float square_size;
	bool fullscreen;
//	coordinate(*grid_coordinates)[gridSize] = new coordinate[gridSize][gridSize];
	coordinate grid_coordinates[8][8];	//matrix dimension must be equal to gridSize

public:
	void init();
	coordinate getGridCoordinate(int col, int row);
	void drawBoard();
	void drawPieces();
	void reshape(int w, int h);
	void mouseBoard(int button, int state, int x, int y);

};

