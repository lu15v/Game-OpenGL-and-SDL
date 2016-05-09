#include "SDL.h"
#include "SDL_opengl.h"
#include <string>

void windowSettings(int width, int height);

void drawingSquares (int myX, int myY, int width, int height, int red, int green, int blue, int alpha);

void drawingSquaresWithImage(int myX, int myY, int width, int height, int red, int green, int blue, int alpha, unsigned int texture);

bool  checkCollision(float Ax, float Ay, float Aw, float Ah, float Bx, float By, float Bw, float Bh);

GLuint loadTexture(const std::string &fileName);

