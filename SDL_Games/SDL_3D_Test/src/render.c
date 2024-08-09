#include <SDL.h>
#include "2DVertex.h"
#include "SDL_state.h"
#include "SDL_state.h"
#include "edges.h"

void drawVertices2D(){
    for (int i = 0; i < vertex2DCount; i++){
        SDL_RenderDrawPoint(state.renderer, vertex2DList[i].x+state.windowWidth/2, -vertex2DList[i].y+state.windowHeight/2);
    }
}

void drawEdge(int index1, int index2){
    SDL_RenderDrawLine(state.renderer, vertex2DList[index1].x +state.windowWidth/2, -vertex2DList[index1].y+state.windowHeight/2, vertex2DList[index2].x+state.windowWidth/2, -vertex2DList[index2].y+state.windowHeight/2);
}

void drawEdges(){
    for (int i = 0; i < edgeCount; i++){
        drawEdge(edgeList[i].index1, edgeList[i].index2);
    }
}