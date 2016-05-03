
/*
-lmingw32 -lSDLmain -lSDL -lopengl32 -lglu32
*/
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>


int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING); /*enable audio joystick everything */

    int widthScreen = 600;
    int heightScreen = 400;
    windowSettings(widthScreen, heightScreen);

    /* main loop */
    bool running = true;

    /* handling events */
    SDL_Event event;

    /* positions of the bar */
    float myX = 300;
    float myY = 375;
    float width = 80;
    float height = 20;

    /* the ball variables */

    float ballX = 50;
    float ballY = 50;
    float ballWH = 25;

    float velX = 0.08;
    float velY = 0.08;

    bool left = false, right = false;


    while (running)
    {
        /* takes events for the event stack */
        while (SDL_PollEvent(&event)){
            if( event.type == SDL_QUIT)
                running = false;
            /* where you find all the keys event... */
            if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_ESCAPE)
                running = false;

            if(event.type == SDL_KEYDOWN){

                if(event.key.keysym.sym == SDLK_LEFT){
                    left = true;
                }
                else if(event.key.keysym.sym == SDLK_RIGHT){
                    right = true;
                }
            }

            else if ( event.type == SDL_KEYUP){

                if (event.key.keysym.sym == SDLK_LEFT){
                    left = false;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT){
                    right = false;
                }
            }
        }
        //logic of the game
        //bar movement
        if (left == true){
            myX -= 0.2;
        }
        if (right == true){
            myX += 0.2;
        }

        //avoid bar to get out of the screen
        if(myX < 0 ){
            myX = 0;
        }
        if (myX + width > widthScreen){
            myX = widthScreen - width;
        }

        //ball logic
        ballX += velX;
        ballY += velY;

        if( ballX < 0){
            velX = -velX;
        }
        else if (ballX + ballWH > widthScreen){
            velX = -velX;
        }

        if(ballY < 0){
            velY = -velY;
        }
        //bottom of the screen the ball hit the bottom
        else if (ballY + ballWH > heightScreen){
            velY = -velY;
            //running = false;
        }

        if(checkCollision(ballX, ballY, ballWH, ballWH, myX, myY, width, height)){
            velY = -velY;
        }

        /*rendering to the screen */
        glClear(GL_COLOR_BUFFER_BIT);

        /* brings the matrix to us */
        glPushMatrix();

        glOrtho(0,widthScreen,heightScreen,0,-1,1); //set the matrix

        drawingSquares(myX, myY, width, height, 0, 0, 0, 255); //bar created

        drawingSquares(ballX, ballY, ballWH, ballWH, 255, 0, 0, 255); //ball created
        /* return to the screen */
        glPopMatrix();
        /* render */
        SDL_GL_SwapBuffers();
    }




    SDL_Quit();

    return 0;
}
