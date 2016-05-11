#include "functions.h"


    /*variables for the textures */
    unsigned int background_texture = 0;
    unsigned int pad_texture = 0;
    unsigned int bar_texture = 0;

    unsigned int blueBrick_texture = 0;
    unsigned int redBrick_texture = 0;
    unsigned int orangeBrick_texture = 0;
    unsigned int yellowBrick_texture = 0;

    unsigned int gameOver_texture = 0;
    unsigned int lifes_texture = 0;

    unsigned int puSize_texture = 0;
    unsigned int puVel_texture = 0;

    unsigned int puLessSize_texture = 0;
    unsigned int puReverse_texture = 0;
    unsigned int puRandom_texture = 0;
    unsigned int puBullets_texture = 0;

    unsigned int bullet_texture = 0;

    unsigned int zero_texture = 0;
    unsigned int one_texture = 0;
    unsigned int two_texture = 0;
    unsigned int three_texture = 0;
    unsigned int four_texture = 0;
    unsigned int five_texture = 0;
    unsigned int six_texture = 0;
    unsigned int seven_texture = 0;
    unsigned int eight_texture = 0;
    unsigned int nine_texture = 0;

    unsigned int score_texture = 0;
    unsigned int level_texture = 0;


unsigned int selectTextureNumber(int select){


switch(select)
   {
   case 0 :
       return zero_texture;
   case 1 :
       return one_texture;
   case 2 :
       return two_texture;
   case 3 :
       return three_texture;
   case 4 :
       return four_texture;
   case 5 :
       return five_texture;
   case 6 :
       return six_texture;
   case 7 :
       return seven_texture;
   case 8 :
       return eight_texture;
   case 9 :
       return nine_texture;
   }


}
