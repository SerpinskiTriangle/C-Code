#include <SDL.h>
#include "SDL_init.h"
#include "SDL_state.h"

void SDL_init(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(state.windowWidth,state.windowHeight,0,&state.window,&state.renderer);
}