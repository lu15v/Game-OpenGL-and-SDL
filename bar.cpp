#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"


void drawingSquares (int myX, int myY, int width, int height, int red, int green, int blue, int alpha){
    glColor4ub(red,green,blue,alpha);//black color from the bar
    glBegin(GL_QUADS);
    glVertex2f(myX, myY);
    glVertex2f(myX + width, myY);
    glVertex2f(myX + width, myY + height);
    glVertex2f(myX, myY + height);
    glEnd();
}

