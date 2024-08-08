#include <SDL.h>
#include "2DVertex.h"
#include "SDL_state.h"

void drawVertices2D(){
    for (int i = 0; i < vertex2DCount; i++){
        SDL_RenderDrawPoint(state.renderer, vertex2DList[i].x, vertex2DList[i].y);
    }
}