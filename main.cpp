
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

GLuint loadTexture(const std::string &fileName){
    /* load image into sdl surface */
    /*filename.c_str converts to string the file name */

    SDL_Surface *image = IMG_Load(fileName.c_str() );

    /*display format */

    SDL_DisplayFormatAlpha(image);

    /*texture */
    unsigned object(0);


    glGenTextures(1, &object);

    glBindTexture(GL_TEXTURE_2D, object);

    //create texture sdl surface (how the texture will behave)

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /*creation of the texture sdl surface */
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->w, image ->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);

    /*free surface */
    SDL_FreeSurface(image);

    return object;
}


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

    float ballX = 420;
    float ballY = 300;
    float ballWH = 25;

    float velX = 0.06;
    float velY = -0.06;

    bool left = false, right = false;
    //Brick elements
    const static int BRICKS = 36; //global quantity of the bricks

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
/*
    unsigned int pad_texture = 0;
    pad_texture = loadTexture("bar.png");

    std::cout << pad_texture << std::endl;

*/
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

        if(checkCollision(ballX, ballY, ballWH, ballWH, myX, myY, width, height)){
            velY = -velY;
        }

        /*rendering to the screen */
        glClear(GL_COLOR_BUFFER_BIT);

        /* brings the matrix to us */
        glPushMatrix();

        glOrtho(0,widthScreen,heightScreen,0,-1,1); //set the matrix

        //for rendering the image to the bar, you have to change the color to white 4 x 255

        drawingSquares(myX, myY, width, height, 0, 0, 0, 255); //bar created

        drawingSquares(ballX, ballY, ballWH, ballWH, 255, 0, 0, 255); //ball created



        for(int i = 0; i < BRICKS; i++){

          if(!bricks[i].isHit){
            if(i < 9)
                drawingSquares(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 0, 0, 255, 255);
            else if (i < 18)
              drawingSquares(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 0, 0, 255);
            else if (i < 27)
             drawingSquares(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 255, 165, 0, 255);
            else
             drawingSquares(bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height, 242, 234, 5, 255);
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
