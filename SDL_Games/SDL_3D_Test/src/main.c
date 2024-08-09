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
#include "edges.h"

unsigned char running;

int main(){
    SDL_init();
    initVertex3DList();
    initVertex2DList();
    initEdgeList();
    running = 1;

    appendVertex3D(-10,-10,-10);
    appendVertex3D(10,-10,-10);
    appendVertex3D(10,-10,10);
    appendVertex3D(-10,-10,10);
    appendVertex3D(-10,10,-10);
    appendVertex3D(10,10,-10);
    appendVertex3D(10,10,10);
    appendVertex3D(-10,10,10);

    appendEdge(0,2);
    appendEdge(1,3);
    appendEdge(1,2);
    appendEdge(0,3);
    appendEdge(0+4,2+4);
    appendEdge(1+4,3+4);
    appendEdge(1+4,2+4);
    appendEdge(0+4,3+4);
    appendEdge(0,0+4);
    appendEdge(1,1+4);
    appendEdge(2,2+4);
    appendEdge(3,3+4);
    
    

    while (running){
        SDL_SetRenderDrawColor(state.renderer, 0,0,0,255);//temporary-ish (idk if/how to encapsulate)
        SDL_RenderClear(state.renderer);

        updateKeyboardState();
        updatePos(&playerCamera.x, &playerCamera.y, &playerCamera.z);   
        
        checkQuit();
        
        fullProjectVertices(vertex3DList, vertex3DCount, vertex2DList, playerCamera);

        SDL_SetRenderDrawColor(state.renderer, 100,100,100,0);
        drawEdges();
        SDL_SetRenderDrawColor(state.renderer, 255,255,255,255);
        drawVertices2D();

        SDL_RenderPresent(state.renderer);

        SDL_Delay(16);//yeah we're not gonna do anything fancy here
        //render
        //update
    }
    cleanVertex3DList();
    cleanVertex2DList();
    cleanEdgeList();
}