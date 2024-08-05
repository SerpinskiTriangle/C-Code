#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "SDL_init.h"
#include "2DVertex.h"
#include "quit.h"

unsigned char running;

int main(){
    SDL_init();
    initVertexList();
    running = 1;
    appendVertex(1,0,-1);
    while (running){
        checkQuit();
        //render
        //update
    }
    cleanVertexList();
}