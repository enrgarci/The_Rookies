#include "Window.h"
#include <iostream>
#include "ETSIDI.h"
#include "freeglut.h"
#include <string.h>


//DO NOT TOUCH THE CODE UNDER THIS LINE, IT'S SACRED

void Window::reshape(int w, int h)
{
    // Update window width and height variables
    //windowWidth = w;
    //windowHeight = h;

    // Defining the viewport and projection
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) {
        glOrtho(0, 1.0, 0 * (GLfloat)h / (GLfloat)w, 1.0 * (GLfloat)h / (GLfloat)w, -1.0, 1.0);
    }
    else {
        glOrtho(0 * (GLfloat)w / (GLfloat)h, 1.0 * (GLfloat)w / (GLfloat)h, 0, 1.0, -1.0, 1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glutSwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT);
}


// Handles the keyboard input when the program is in fullscreen mode
// If the program is currently in fullscreen mode, pressing escape will switch to windowed mode, and vice versa.
void Window::keyboardFullscreen(unsigned char key, int x, int y)
{
    const char ESCAPE_KEY = 27;
    if (key == ESCAPE_KEY)
    {
        if (Window::fullscreen)
        {
            glutReshapeWindow(Window::screen_width, Window::screen_height);
            fullscreen = false;
        }
        else
        {
            glutFullScreen();
            fullscreen = true;
        }
    }
}
