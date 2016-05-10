// 37 y 315
/*
-lmingw32 -lSDLmain -lSDL -lopengl32 - -lSDL_image
*/
#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>
#include "SDL_image.h"
#include "structs.h"
#include <windows.h>
#include <time.h>
#include <ctime>

int main (int argc, char* args[])
{


    SDL_Init(SDL_INIT_EVERYTHING); /*enable audio joystick everything */

    int widthScreen = 650;
    int heightScreen = 500;
    int limits = 400;
    windowSettings(widthScreen, heightScreen);


    /*count how many bricks were destroyed */
    int destroyedBricks = 0;

   // int bricksForPowerUps = 0;

    /* total Score */
    int score = 0;

    /*lifes */
    int lifes = 999;

    /* main loop */
    bool running = true;

    /* handling events */
    SDL_Event event;

    /* timers for the powerUps */
    clock_t start;
    clock_t finish;
    /* positions of the bar */
    float myX = 300;
    float myY = 375;
    float width = 80;
    float height = 20;
    float barVelocity = 0.2;

    /*positions of the bullet */
    float bulletX = 325;
    float bulletY = 375;
    float bulletWidth = 30;
    float bulletHeight = 50;
    float bulletVelocity = 0.2;

    /* the ball variables */

    float ballX = 420;
    float ballY = 300;
    float ballWH = 25;

    float velX = 0.1;
    float velY = -0.1;
    float limit = -1.10;
    /* lifes */
    const static int NOLIFES = 3;
    Lifes tLifes[NOLIFES];

    /* random variables */
    int powerProbability, randomPower, random;

    /* power up movement */
    const static int TOTALPOWERUPS = 6;
    PowerUp powerUp[TOTALPOWERUPS];

    /* enable power up */
    bool power;
    bool selected = true;
    bool reversed = false;
    bool bullet = false;
   // float puWH = 25;
    /*power up velocity */
    float movY = -0.05;

    bool left = false, right = false, up = false;
    //Brick elements
    const static int BRICKS = 36; //global quantity of the bricks
    Brick bricks[BRICKS];



    for(int i = 0; i < TOTALPOWERUPS; i++ ){
        powerUp[i].x = widthScreen / 2;
        powerUp[i].y = 120;
        powerUp[i].width = 25;
        powerUp[i].height = 25;
        powerUp[i].isHit = false;

    }


    for (int i = 0, x = 4, y = 450; i < NOLIFES; i++, x+= 52){
           if(x > 597){
            x = 4;
            y += 25;
        }
        tLifes[i].x = x;
        tLifes[i].y = y;
        tLifes[i].width = 40;
        tLifes[i].height = 30;
        tLifes[i].left = false;

    }

    for (int i = 0, x = 4, y = 10; i < BRICKS; i++, x+= 72){

        //for accommodate the bricks
        if(x > 597){
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


    unsigned int gameOver_texture = 0;
    gameOver_texture = loadTexture("gameOver.png");

    unsigned int puSize_texture = 0;
    puSize_texture = loadTexture("puSize.png");

    unsigned int puVel_texture = 0;
    puVel_texture  = loadTexture("puVelo.png");

    unsigned int lifes_texture = 0;
    lifes_texture = loadTexture("life.png");


    unsigned int puLessSize_texture = 0;
    puLessSize_texture = loadTexture("puLessSize.png");

    unsigned int puReverse_texture = 0;
    puReverse_texture = loadTexture("puReverse.png");

    unsigned int puRandom_texture = 0;
    puRandom_texture = loadTexture("puRandom.png");

    unsigned int puBullets_texture = 0;
    puBullets_texture = loadTexture("puBullets.png");

    unsigned int bullet_texture = 0;
    bullet_texture = loadTexture("bullet.png");

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

            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
                 system("PAUSE");

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
            if(event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP){
                up = true;
            }

        }
        //logic of the game
        //bar movement
        if (left == true){
            if(!reversed){
                myX -= barVelocity;
                if(bulletY == 375)
                    bulletX -= barVelocity;
            }

            else{
                myX += barVelocity;
            }
        }
        if (right == true){
            if(!reversed){
                myX += barVelocity;
                if(bulletY == 375 )
                    bulletX += barVelocity;
            }
            else{
               myX -= barVelocity;
            }
        }

        //avoid bar to get out of the screen
        if(myX < 0 ){
            myX = 0;
            bulletX = myX + 25;
        }
        if (myX + width > widthScreen){
            myX = widthScreen - width;
            bulletX = myX + 25;
        }


        //power up logic

        if(selected){
            srand((int)time(0));
            powerProbability = rand() % 100 + 1;

            randomPower = rand() % 6;
            if(powerProbability > 1){
                power = true;
                selected = false;
            }

        }


        if(power && !powerUp[randomPower].isHit){
            powerUp[randomPower].y -= movY;
        }

        if(bullet && up)
            bulletY -= bulletVelocity;

        if (powerUp[randomPower].y + powerUp[randomPower].height > limits)
            start = clock();

        if(!powerUp[randomPower].isHit && checkCollision(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, myX, myY, width, height)){
            powerUp[randomPower].isHit = true;

            start = clock();

            if(randomPower == 4)
                random = rand() % 4;
            if(randomPower == 0 || randomPower == 4 && random == 0)
                width = 120;
            if(randomPower == 1 || randomPower == 4 && random == 1)
                barVelocity = 0.4;
            if(randomPower == 2 || randomPower == 4 && random == 2)
                width = 50;
            if(randomPower == 3 || randomPower == 4 && random == 3)
                reversed = true;
            if(randomPower == 5)
                bullet = true;



        }



        finish = clock();


        if(((finish - start) / CLOCKS_PER_SEC) == 4){
            if(randomPower == 0 || randomPower == 2 || random == 0 || random == 2)
                width = 80;
            if(randomPower == 1 || random == 1)
                barVelocity = 0.2;
            if(randomPower == 3 || random == 3)
                reversed = false;
            if(randomPower == 5){
                bulletY = myY;
                bulletX = myX + 25;
                bullet = false;
            }

             powerUp[randomPower].isHit = false;
             powerUp[randomPower].y = 120;
             power = false;
             selected = true;
        }
        if (powerUp[randomPower].y + powerUp[randomPower].height > limits)
        {
            powerUp[randomPower].y = 120;
            power = false;
            selected = true;
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
                    score += 10;
                    //std::cout << score; //check the txt in bin
                    break; //not check for aditional collitions.
                }
                if(checkCollision(bulletX, bulletY, bulletWidth, bulletHeight, bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height)){
                velX = - velX;
                bricks[i].isHit = true;
                destroyedBricks += 1;
                score += 10;
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
                    score += 10;
                    //std::cout << score; //check the txt in bin
                    break; //not check for aditional collitions.
                }
                if(checkCollision(bulletX, bulletY, bulletWidth, bulletHeight, bricks[i].x, bricks[i].y, bricks[i].width, bricks[i].height)){
                velX = - velX;
                bricks[i].isHit = true;
                destroyedBricks += 1;
                score += 10;
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
        else if (ballY + ballWH > limits){
            velY = -velY;
          ////  tLifes[lifes].left = true;
            lifes -= 1;
            //std::cout << lifes;
            //running = false;
        }
        else if (bulletX + bulletY < 0)
            up = false;

        else if (destroyedBricks == BRICKS){


         destroyedBricks = 0;

        /* Starting position of the ball */
          ballX = 420;
          ballY = 300;
          ballWH = 25;

          velY = -velY;

          myX = 300; //starting x position of rectangle
          myY = 375; //starting y position of rectangle
          width = 80; //width of the rectangle
          height = 20; //height of the rectangle

          bulletY = myY;
          bulletX = myX + 25;
          up = false;


          left = false,right = false; //Set the buttons back to false



            //restart the bricks
            for ( int n = 0; n < BRICKS; n++ )
            {
              bricks[n].isHit = false;
            }

            Sleep(3000);
        }

        if(checkCollision(ballX, ballY, ballWH, ballWH, myX, myY, width, height)){
            velY = -velY;
            velX = -velX - 0.05;
            //check the middle of the ball
/*
            float middleOfBall = ballX + ballWH/2;
            middleOfBall = middleOfBall - myX; //subtracting the pad' position
            middleOfBall = middleOfBall - 30;
            middleOfBall = middleOfBall / 100;
            velX = middleOfBall;

            */

        }

         /*avoids that the ball reaches unplayable velocities */
        if(velX < limit)
            velX = -0.1;


        /*rendering to the screen */
        glClear(GL_COLOR_BUFFER_BIT);

        /* brings the matrix to us */
        glPushMatrix();

        glOrtho(0,widthScreen,heightScreen,0,-1,1); //set the matrix

        //for rendering the image to the bar, you have to change the color to white 4 x 255


        if(lifes > -1){
            drawingSquaresWithImage(0, 0, widthScreen, heightScreen, 255, 255, 255, 255, background_texture);

            drawingSquaresWithImage(myX, myY, width, height, 255, 255, 255, 255, bar_texture); //bar created

            drawingSquaresWithImage(ballX, ballY, ballWH, ballWH, 255, 255, 255, 255, pad_texture); //ball created

            if(bullet)
                drawingSquaresWithImage(bulletX, bulletY, bulletWidth, bulletHeight, 255, 255, 255, 255, bullet_texture);


            if(power && !powerUp[randomPower].isHit && powerUp[randomPower].y + powerUp[randomPower].height < limits ){
                if(randomPower == 0)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puSize_texture); //size Power Up created
                else if(randomPower == 1)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puVel_texture);
                else if(randomPower == 2)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puLessSize_texture);
                else if(randomPower == 3)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puReverse_texture);
                else if(randomPower == 4)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puRandom_texture);
                else if(randomPower == 5)
                    drawingSquaresWithImage(powerUp[randomPower].x, powerUp[randomPower].y, powerUp[randomPower].width, powerUp[randomPower].height, 255, 255, 255, 255, puBullets_texture);
            }



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

         for(int i = 0; i < NOLIFES; i++){
            if(!tLifes[i].left)
            drawingSquaresWithImage(tLifes[i].x, tLifes[i].y, tLifes[i].width, tLifes[i].height, 255, 255, 255, 255, lifes_texture);
         }

        }else{
            drawingSquaresWithImage(0, 0, widthScreen, heightScreen, 255, 255, 255, 255, gameOver_texture);

        }


        /* return to the screen */
        glPopMatrix();
        /* render */
        SDL_GL_SwapBuffers();
    }




    SDL_Quit();

    return 0;
}
