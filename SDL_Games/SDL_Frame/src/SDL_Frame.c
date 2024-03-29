#include <SDL.h>
#include <math.h>
#include <unistd.h>

#define CLASS_COUNT 3


int8_t still;
const Uint8 *keyboardState;
const int playerHeight = 50;
const int playerWidth = 50;
int frame = 0;
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
    float moveAngleRad;
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
        SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
        SDL_RenderClear(state.renderer);
        while (SDL_PollEvent(&state.event)){
            if (state.event.type == SDL_QUIT){
                state.running = 0;
                break;
            }
        }
        keyboardState = SDL_GetKeyboardState(NULL);
        if (!(keyboardState[SDL_SCANCODE_W] || keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_A] || keyboardState[SDL_SCANCODE_D])){
            still = 1;
            player.xSpeed = 0;
            player.ySpeed = 0;
        }
        else {
            player.moveAngleRad = atan2(keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W], keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]);
            
            player.xSpeed = cos(player.moveAngleRad);
            player.ySpeed = sin(player.moveAngleRad);

            player.hitbox.x += 5 * player.xSpeed;
            player.hitbox.y += 5 * player.ySpeed;
        }//quite silly indeed

        //debug section
        printf("\rMovAng: %-6f xSpeed: %-6f ySpeed: %-6f scnW: %d scnA: %d scnS: %d scnD: %d",player.moveAngleRad,player.xSpeed,player.ySpeed,keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_A],keyboardState[SDL_SCANCODE_S],keyboardState[SDL_SCANCODE_D]);
        fflush(stdout);
        SDL_SetRenderDrawColor(state.renderer,255,255,255,255);
        SDL_RenderDrawRect(state.renderer,&player.hitbox);
        SDL_RenderPresent(state.renderer);
        SDL_Delay(16);


        frame++;
    }
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}