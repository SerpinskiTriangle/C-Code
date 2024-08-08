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
#include "camera.h"
#include "SDL_keyboardState.h"
#include "movement.h"

unsigned char running;

int main(){
    SDL_init();
    initVertex3DList();
    initVertex2DList();
    running = 1;

    appendVertex3D(-10,-10,-10);
    appendVertex3D(10,-10,-10);
    appendVertex3D(-10,-10,10);
    appendVertex3D(10,-10,10);
    appendVertex3D(-10,10,-10);
    appendVertex3D(10,10,-10);
    appendVertex3D(-10,10,10);
    appendVertex3D(10,10,10);

    while (running){
        SDL_SetRenderDrawColor(state.renderer, 0,0,0,255);//temporary-ish (idk if/how to encapsulate)
        SDL_RenderClear(state.renderer);
        SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);

        updateKeyboardState();
        updatePos(&playerCamera.x, &playerCamera.y, &playerCamera.z);   
        
        checkQuit();
        fullProjectVertices(vertex3DList, vertex3DCount, vertex2DList, playerCamera);

        drawVertices2D();
        SDL_RenderPresent(state.renderer);

        SDL_Delay(16);//yeah we're not gonna do anything fancy here
        //render
        //update
    }
    cleanVertex3DList();
    cleanVertex2DList();
}