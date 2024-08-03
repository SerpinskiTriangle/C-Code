#include <SDL.h>
#include "quit.h"
#include "main.h"


SDL_Event currentSDL_event;

void checkQuit(){
    while (SDL_PollEvent(&currentSDL_event)){
            if (currentSDL_event.type == SDL_QUIT){
                running = 0;
        }
    }
}