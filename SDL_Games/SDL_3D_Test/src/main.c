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

    appendVertex3D(-2,-2,-2);
    appendVertex3D(2,-2,-2);
    appendVertex3D(2,-2,2);
    appendVertex3D(-2,-2,2);

    appendVertex3D(-2,2,-2);
    appendVertex3D(2,2,-2);
    appendVertex3D(2,2,2);
    appendVertex3D(-2,2,2);

    appendEdge(0,1);
    appendEdge(1,2);
    appendEdge(2,3);
    appendEdge(3,0);

    appendEdge(0+4,1+4);
    appendEdge(1+4,2+4);
    appendEdge(2+4,3+4);
    appendEdge(3+4,0+4);

    appendEdge(0,0+4);
    appendEdge(1,1+4);
    appendEdge(2,2+4);
    appendEdge(3,3+4);


    while (running){
        SDL_SetRenderDrawColor(state.renderer, 0,0,0,255);//temporary-ish (idk if/how to encapsulate)
        SDL_RenderClear(state.renderer);

        updateKeyboardState();
        updatePos(&playerCamera.x, &playerCamera.y, &playerCamera.z);
        updateRotation(&playerCamera.angleYaw,&playerCamera.anglePitch);
        printf("yaw%e, pitch%e\r", playerCamera.angleYaw, playerCamera.anglePitch);
        
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

    printf("\n");
}