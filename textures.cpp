#include "SDL.h"
#include "SDL_opengl.h"
#include <iostream>
#include "functions.h"
#include <string>
#include "SDL_image.h"



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
