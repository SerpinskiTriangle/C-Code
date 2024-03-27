#include <SDL.h>
#include <math.h>

#define CLASS_COUNT 3


int8_t still;
const Uint8 *keyboardState;
const int playerHeight = 50;
const int playerWidth = 50;
struct state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    const int windowWidth;
    const int windowHeight;
    int running;
};

struct state state = {NULL,NULL,NULL,600,600,1};


struct entity{
    float xSpeed;
    float ySpeed;
    SDL_Rect hitbox;
    int faceAngleDeg;
    int moveAngleDeg;
};

struct entity player = {0,0,{0,0,playerHeight, playerWidth},0,0};

struct entity ***gameEntities[CLASS_COUNT];    
/* ok please dont laugh i promise this is for memory efficiency
 * all entities are in a hierarchy (class > type > individual entity)
 *
 */







int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(state.windowWidth,state.windowHeight,0,&state.window,&state.renderer);

    SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
    SDL_RenderClear(state.renderer);

    

    while (state.running){
        while (SDL_PollEvent(&state.event)){
            if (state.event.type == SDL_QUIT){
                state.running = 0;
                break;
            }
        }
        keyboardState = SDL_GetKeyboardState(NULL);
        if (!(keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_D])){
            still = 1;
        }
        else {
            player.moveAngleDeg = atan2(keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W], keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]);
        }//quite silly indeed
        SDL_SetRenderDrawColor(state.renderer,255,255,255,255);
        SDL_RenderDrawRect(state.renderer,&player.hitbox);


    }
    return 0;
}