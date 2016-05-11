#include "SDL.h"
#include "SDL_opengl.h"
#include "SDL_image.h"
#include <SDL_image.h>
#include <SDL_ttf.h>


bool loadFonts();
void initFonts();
TTF_Font* Font = NULL;

bool loadFonts()
{
    //Load main font
    char font_main[] = "media/fonts/Akura Popo.ttf";
    Font = TTF_OpenFont(font_main, 30);
    if (Font == NULL)
        return false;
    return true;
}
void initFonts()
{
    if (TTF_Init() == -1)
    {
        printf("Failed to initialize Fonts");
    }
    if(!loadFonts())
    {
        printf("Failed to load fonts!\n");
        TTF_CloseFont(Font);
        TTF_Quit();
        SDL_Quit();
    }
}
