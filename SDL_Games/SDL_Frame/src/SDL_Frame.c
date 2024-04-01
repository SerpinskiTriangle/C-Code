#include <SDL.h>
#include <math.h>
#include <unistd.h>

//this looks atrocious because i want a working demo of everything before i make it scalable to innumerable entities

#define CLASS_COUNT 3


int8_t still;
const Uint8 *keyboardState;
const int playerHeight = 50;
const int playerWidth = 50;
int frame = 0;
int collide = 0;
struct state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    const int windowWidth;
    const int windowHeight;
    int running;
};

struct state state = {NULL,NULL,{NULL},600,600,1};


struct entity{
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    int height;
    int width;
    int faceAngleDeg;
    float moveAngleRad;
};

struct entity player = {0,0,0,0,playerHeight, playerWidth,0,0};
struct entity test = {300,300,0,0,100,100,0,0};

struct entity ***gameEntities[CLASS_COUNT];    
/* ok please dont laugh i promise this is for memory efficiency
 * all entities are in a hierarchy (class > type > individual entity)
 *
 */




void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w);

int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W);


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

        if (!(keyboardState[SDL_SCANCODE_W] - keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_A] - keyboardState[SDL_SCANCODE_D])){
            still = 1;
            player.xSpeed = 0;
            player.ySpeed = 0;
        }
        else {
            player.moveAngleRad = atan2(keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W], keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]);
            
            player.xSpeed = cos(player.moveAngleRad);
            player.ySpeed = sin(player.moveAngleRad);
        }//quite silly indeed

        if (collideStatus(player.xPos + player.xSpeed * 5,player.yPos,player.height,player.width,test.xPos,test.yPos,test.height,test.width)){
            player.xSpeed = 0;
        }
        if (collideStatus(player.xPos,player.yPos + player.ySpeed * 5,player.height,player.width,test.xPos,test.yPos,test.height,test.width)){
            player.ySpeed = 0;
        }

        player.xPos += 5 * player.xSpeed;
        player.yPos += 5 * player.ySpeed;
        //debug section
        printf("\rMovAng/pi: %-+6f xSpeed: %-+6f ySpeed: %-+6f scnW: %d scnA: %d scnS: %d scnD: %d",player.moveAngleRad / 3.1415926,player.xSpeed*5,player.ySpeed*5,keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_A],keyboardState[SDL_SCANCODE_S],keyboardState[SDL_SCANCODE_D]);
        fflush(stdout);

        collide = collideStatus(player.xPos,player.yPos,player.height,player.width,test.xPos,test.yPos,test.height,test.width);

        SDL_SetRenderDrawColor(state.renderer,255,255 * !collide,255 * !collide,255);
        drawEntHitbox(state.renderer,player);
        drawEntHitbox(state.renderer,test);
        SDL_RenderPresent(state.renderer);
        SDL_Delay(16);
        
        frame++;
    }
    printf("\n");
    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}


void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w){
    SDL_RenderDrawLine(renderer,x,y,x+w,y);
    SDL_RenderDrawLine(renderer,x,y,x,y+h);
    SDL_RenderDrawLine(renderer,x+w,y+h,x+w,y);
    SDL_RenderDrawLine(renderer,x+w,y+h,x,y+h);
}


int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W){
    return(
        (ent1X + ent1W >= ent2X)&&
        (ent1X <= ent2X + ent2W)&&
        (ent1Y + ent1H >= ent2Y)&&
        (ent1Y <= ent2Y + ent2H)
    );
}//its not unreadable, its optimized (trust)

void drawEntHitbox(struct SDL_renderer *renderer, struct entity entity){
    drawRect(renderer,entity.xPos,entity.yPos,entity.height,entity.width);
}