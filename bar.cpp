#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>
#include "SDL_image.h"

void drawingSquares (int myX, int myY, int width, int height, int red, int green, int blue, int alpha){
    glColor4ub(red,green,blue,alpha);//black color from the bar
    glBegin(GL_QUADS); //rendering
    glVertex2f(myX, myY);
    glVertex2f(myX + width, myY);
    glVertex2f(myX + width, myY + height);
    glVertex2f(myX, myY + height);
    glEnd();
}


void drawingSquaresWithImage (int myX, int myY, int width, int height, int red, int green, int blue, int alpha, unsigned int texture){
    glColor4ub(red,green,blue,alpha);//black color from the bar
    //for blending the image
    glEnable(GL_TEXTURE_2D);

    //specify which texture you will blind
    glBindTexture(GL_TEXTURE_2D, texture);
    glBegin(GL_QUADS); //rendering

    /*for specify image dimentions */
    glTexCoord2d(0,0); glVertex2f(myX, myY); //Upper left corner
    glTexCoord2d(1,0); glVertex2f(myX + width, myY); //upper right corner
    glTexCoord2d(1,1); glVertex2f(myX + width, myY + height); //Down right corner
    glTexCoord2d(0,1); glVertex2f(myX, myY + height); //Down left corner
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
