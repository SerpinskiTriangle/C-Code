#include <stdio.h>
#include "main.h"
#include "SDL_init.h"
#include "vertex.h"

int main(){
    SDL_init();
    initVertexList();
    running = 1;
    while (running){
        //render
        //update
    }
    cleanVertexList();
}