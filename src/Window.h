#pragma once
class Window
{
	int screen_width;
	int screen_height;
	bool fullscreen;





public:

	Window() { screen_width = 800;  screen_height = 600; }
	void reshape(int w, int h);
	void keyboardFullscreen(unsigned char key, int x, int y);
	void draw();
	void mouse(int button, int state, float xMouse, float yMouse);

};

