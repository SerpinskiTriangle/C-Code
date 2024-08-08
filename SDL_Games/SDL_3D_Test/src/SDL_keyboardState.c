#include "SDL_keyboardState.h"
#include <SDL.h>

const unsigned char *keyboardState;

void updateKeyboardState(){
    keyboardState = SDL_GetKeyboardState(NULL);
}