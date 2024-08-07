#include <stdio.h>
#include <SDL.h>
#include "main.h"
#include "SDL_init.h"
#include "3DVertex.h"
#include "2DVertex.h"
#include "quit.h"
#include "project.h"

unsigned char running;

int main(){
    SDL_init();
    initVertex3DList();
    initVertex2DList();
    running = 1;
    appendVertex3D(1,0,-1);
    while (running){
        checkQuit();
        projectVertices();
        //render
        //update
    }
    cleanVertex3DList();
    cleanVertex2DList();
}