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

    appendVertex3D(1,0, 0);
    appendVertex3D(0,1, 0);
    appendVertex3D(-1,0, 0);
    appendVertex3D(0,-1, 0);

    appendVertex3D(0,-10, 0);
    appendVertex3D(4,-2, 0);
    appendVertex3D(4,2, 0);
    appendVertex3D(-5,2, 0);
    appendVertex3D(-7,-1, 0);
    appendVertex3D(-7,-10, 0);

    appendVertex3D(8,0,0);

    appendVertex3D(-10,2,0);
    appendVertex3D(-3,4,0);
    appendVertex3D(0,10,0);
    appendVertex3D(3,4,0);
    appendVertex3D(10,2,0);

    appendEdge(0,1);
    appendEdge(1,2);
    appendEdge(2,3);
    appendEdge(3,0);

    appendEdge(4,5);
    appendEdge(5,6);
    appendEdge(6,7);
    appendEdge(7,8);
    appendEdge(8,9);

    appendEdge(5,10);
    appendEdge(6,10);

    appendEdge(11,12);
    appendEdge(12,13);
    appendEdge(13,14);
    appendEdge(14,15);
    appendEdge(15,11);

    while (running){
        SDL_SetRenderDrawColor(state.renderer, 0,0,0,255);//temporary-ish (idk if/how to encapsulate)
        SDL_RenderClear(state.renderer);

        updateKeyboardState();
        updatePos(&playerCamera.x, &playerCamera.y, &playerCamera.z);
        printf("x%e, y%e, z%e\r", playerCamera.x, playerCamera.y,playerCamera.z);
        
        checkQuit();
        
        fullProjectVertices(vertex3DList, vertex3DCount, vertex2DList, playerCamera);

        SDL_SetRenderDrawColor(state.renderer, 10,10,10,0);
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