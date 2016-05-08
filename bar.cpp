#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>
#include "SDL_image.h"

void drawingSquares (int myX, int myY, int width, int height, int red, int green, int blue, int alpha){
    glColor4ub(red,green,blue,alpha);//black color from the bar
    glBegin(GL_QUADS); //rendering
    glVertex3f(myX, myY, 0);
    glVertex3f(myX + width, myY, 0);
    glVertex3f(myX + width, myY + height, 0);
    glVertex3f(myX, myY + height, 0);
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
    glTexCoord2d(0,0); glVertex3f(myX, myY, 0); //Upper left corner
    glTexCoord2d(1,0); glVertex3f(myX + width, myY, 0); //upper right corner
    glTexCoord2d(1,1); glVertex3f(myX + width, myY + height, 0); //Down right corner
    glTexCoord2d(0,1); glVertex3f(myX, myY + height, 0); //Down left corner
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
