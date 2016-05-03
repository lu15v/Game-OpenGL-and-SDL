#include "functions.h"


bool  checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh)
{
    //rectangle A over rentangle B
    if( Ay + Ah < By) return false;
    else if( Ay > By + Bh) return false;
    else if(Ax + Aw < Bx) return false;
    else if(Ax > Bx + Bw) return false;

    return true;
}

