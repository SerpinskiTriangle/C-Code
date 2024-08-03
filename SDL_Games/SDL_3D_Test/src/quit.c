#include <SDL.h>
#include "quit.h"
#include "main.h"
#include "SDL_state.h"


SDL_Event currentSDL_event;

void checkQuit(){
    while (SDL_PollEvent(&currentSDL_event)){
            if (currentSDL_event.type == SDL_QUIT){
                running = 0;
                SDL_DestroyWindow(state.window);
                SDL_Quit();
        }
    }
}