
/*
-lmingw32 -lSDLmain -lSDL -lopengl32 - -lSDL_image
*/
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>
#include "SDL_image.h"

struct Brick
{
 float x;
 float y;
 float width;
 float height;
 bool isHit;
};



int main (int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING); /*enable audio joystick everything */

    int widthScreen = 600;
    int heightScreen = 400;
    windowSettings(widthScreen, heightScreen);

    /*count how many bricks were destroyed */
    int destroyedBricks = 0;

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

    float ballX = 420;
    float ballY = 300;
    float ballWH = 25;

    float velX = 0.06;
    float velY = -0.06;

    bool left = false, right = false;
    //Brick elements
    const static int BRICKS = 1; //global quantity of the bricks
    Brick bricks[BRICKS];


    for (int i = 0, x = 4, y = 10; i < BRICKS; i++, x+= 66){

        //for accommodate the bricks
        if(x > 560){
            x = 4;
            y += 25;
        }
        bricks[i].x = x;
        bricks[i].y = y;
        bricks[i].width = 60;
        bricks[i].height = 20;
        bricks[i].isHit = false;
    }

    /*load the image 60 40  verify to add the alpha channel*/

    unsigned int background_texture = 0;
    background_texture = loadTexture("backgr.png");

    unsigned int pad_texture = 0;
    pad_texture = loadTexture("ball.png");

    unsigned int bar_texture = 0;
    bar_texture = loadTexture("bar.png");

    unsigned int blueBrick_texture = 0;
    blueBrick_texture = loadTexture("blueBrick.png");

    unsigned int redBrick_texture = 0;
    redBrick_texture = loadTexture("redBrick.png");

    unsigned int orangeBrick_texture = 0;
    orangeBrick_texture = loadTexture("orangeBrick.png");

    unsigned int yellowBrick_texture = 0;
    yellowBrick_texture = loadTexture("yellowBrick.png");




    //std::cout << pad_texture << std::endl;


    /* main loop */
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


        for(int i = 0; i < BRICKS; i++){

            if(!bricks[i].isHit){
                    //ball
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height)){
                    velX = - velX;
                    bricks[i].isHit = true;
                    destroyedBricks += 1;
                    break; //not check for aditional collitions.
                }
            }
        }

        ballY += velY; //if the collision succeeds, then change the movement of the ball

        for(int i = 0; i < BRICKS; i++){

            if(!bricks[i].isHit){
                    //ball
                if(checkCollision(ballX, ballY, ballWH, ballWH, bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height)){
                    velY = - velY;
                    bricks[i].isHit = true;
                    destroyedBricks += 1;
                    break; //not check for aditional collitions.
                }
            }
        }

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
        else if (destroyedBricks == BRICKS){

         destroyedBricks = 0;

        /* Starting position of the ball */
          ballX = 420;
          ballY = 300;
          ballWH = 25;

          velY = -velY;

          myX = 300; //starting x position of rectangle
          myY = 370; //starting y position of rectangle
          width = 80; //width of the rectangle
          height = 20; //height of the rectangle

          left = false,right = false; //Set the buttons back to false


            //restart the bricks
            for ( int n = 0; n < BRICKS; n++ )
            {
              bricks[n].isHit = false;
            }
        }

        if(checkCollision(ballX, ballY, ballWH, ballWH, myX, myY, width, height)){
            velY = -velY;

            //check the middle of the ball
            /*
            float middleOfBall = ballX + ballWH/2;
            middleOfBall = middleOfBall - myX; //subtracting the pad' position
            middleOfBall = middleOfBall - 30;
            middleOfBall = middleOfBall / 100;
            velX = middleOfBall;
            */
        }

        /*rendering to the screen */
        glClear(GL_COLOR_BUFFER_BIT);

        /* brings the matrix to us */
        glPushMatrix();

        glOrtho(0,widthScreen,heightScreen,0,-1,1); //set the matrix

        //for rendering the image to the bar, you have to change the color to white 4 x 255

        drawingSquaresWithImage(0, 0, widthScreen, heightScreen, 255, 255, 255, 255, background_texture);

        drawingSquaresWithImage(myX, myY, width, height, 255, 255, 255, 255, bar_texture); //bar created

        drawingSquaresWithImage(ballX, ballY, ballWH, ballWH, 255, 255, 255, 255, pad_texture); //ball created



        for(int i = 0; i < BRICKS; i++){

          if(!bricks[i].isHit){
            if(i < 9)
                drawingSquaresWithImage(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 255, 255, 255, blueBrick_texture);
            else if (i < 18)
              drawingSquaresWithImage(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 255, 255, 255, redBrick_texture);
            else if (i < 27)
             drawingSquaresWithImage(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 255, 255, 255, orangeBrick_texture);
            else
             drawingSquaresWithImage(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 255, 255, 255, yellowBrick_texture);
          }
        }

        /* return to the screen */
        glPopMatrix();
        /* render */
        SDL_GL_SwapBuffers();
    }




    SDL_Quit();

    return 0;
}
