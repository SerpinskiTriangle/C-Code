#include "movement.h"
#include "SDL_keyboardState.h"
#include <SDL.h>

void updatePos(double *xPos, double *yPos, double *zPos){//temporary movement system for making the rendering part of the engine
    *xPos += keyboardState[SDL_SCANCODE_D]-keyboardState[SDL_SCANCODE_A];
    *yPos += keyboardState[SDL_SCANCODE_R]-keyboardState[SDL_SCANCODE_F];
    *zPos += keyboardState[SDL_SCANCODE_W]-keyboardState[SDL_SCANCODE_S];
}