
/*
-lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32
*/
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>


int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING); /*enable audio joystick everything */

  /*How many memory you provide to opengl */

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    /* window   name of the window*/

    SDL_WM_SetCaption("GAME NAME", NULL);

    /* how big the window be  W T*/

    SDL_SetVideoMode(600,400, 32, SDL_OPENGL);

    /* Color when clear the screen */

    glClearColor(1,1,1,1);

    /* portion to display */

    glViewport(0,0,600,400);

    /*shader model  SMOOTH TRANSLATION nice*/
    glShadeModel(GL_SMOOTH);

    /*only 2d rendering */
    glMatrixMode(GL_PROJECTION);

    /*load */
    glLoadIdentity();

    /* disable depth checking (3d) */
    glDisable(GL_DEPTH_TEST);

    /* main loop */
    bool running = true;

    /* handling events */
    SDL_Event event;

    while (running)
    {
        /* takes events for the event stack */
        while (SDL_PollEvent(&event)){
            if( event.type == SDL_QUIT)
                running = false;
            /* where you find all the keys event... */
            if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;
        }

        /*rendering to the screen */

        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapBuffers();
    }




    SDL_Quit();

    return 0;
}
