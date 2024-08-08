#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "SDL_state.h"
#include "SDL_init.h"
#include "3DVertex.h"
#include "2DVertex.h"
#include "quit.h"
#include "project.h"
#include "render.h"

unsigned char running;

int main(){
    SDL_init();
    initVertex3DList();
    initVertex2DList();
    running = 1;
    appendVertex3D(10,10,1);
    while (running){
        SDL_SetRenderDrawColor(state.renderer, 0,0,0,255);//temporary-ish (idk if/how to encapsulate)
        SDL_RenderClear(state.renderer);
        SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);
        
        checkQuit();
        projectVertices();

        drawVertices2D();
        SDL_RenderPresent(state.renderer);
        //render
        //update
    }
    cleanVertex3DList();
    cleanVertex2DList();
}