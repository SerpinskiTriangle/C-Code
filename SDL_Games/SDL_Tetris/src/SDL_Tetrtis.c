#include <SDL.h>


//sdl stuff
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

SDL_Event event;

//const stuff for later
const int fieldWidth = 10;
const int fieldHeight = 20;

const int windowWidth = 600;
const int windowHeight = 600;

//stuff dependant on previous declarations
uint8_t field[fieldWidth][fieldHeight]; //i hate multidimensional arrays

//silly variables
int running = 0;



 

int main(){
    //and then he said "its initializin time" and he initialized all over the place
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth,windowHeight,0,&window,&renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    while (running){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }
    }
    return 0;
}