#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>


void windowSettings(int width, int height){
    /*How many memory you provide to opengl */



    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* window   name of the window*/

    SDL_WM_SetCaption("Bricks", NULL);

    /* how big the window be  W T*/

    SDL_SetVideoMode(width,height, 32, SDL_OPENGL);

    /* Color when clear the screen */

    glClearColor(1,1,1,1);

    /* portion to display */

    glViewport(0,0,width,height);


    /*shader model  SMOOTH TRANSLATION nice*/
    glShadeModel(GL_SMOOTH);

    /*only 2d rendering */
    glMatrixMode(GL_PROJECTION);

    /*load */
    glLoadIdentity();

    /* disable depth checking (3d) */
    glDisable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


}




