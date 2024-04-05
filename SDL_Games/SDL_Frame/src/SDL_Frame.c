#include <SDL.h>
#include <math.h>
#include <unistd.h>

#define TAG_WALL           (1 << 1)
#define TAG_ENTITY         (1 << 2)
#define TAG_PROJECTILE     (1 << 3)
#define TAG_PLAYER         (1 << 4)
#define TAG_PLAYER_SEEKING (1 << 5)

#define MAX_ENTITY_COUNT 7
//this looks atrocious because i want a working demo of everything before i make it scalable to innumerable entities



const Uint8 *keyboardState;
int entityCount = 0;
struct state {
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    const int windowWidth;
    const int windowHeight;
    int running;
};

struct state state = {NULL,NULL,{0},600,600,1};


struct entity{
    float xPos;
    float yPos;
    float xSpeed;
    float ySpeed;
    int width;
    int height;
    float entSpeed;
    int faceAngleDeg;
    float moveAngleRad;
    int tags; //pointers equal to NULL are treated as the end
};


struct entity **gameEntities;


int *allocTable;


void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w);

void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity);

int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W);

void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int width, int height, float entSpeed, int faceAngleDeg, float moveAngleRad, int tags);

float genPlayerMovAnglRad();



int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(state.windowWidth,state.windowHeight,0,&state.window,&state.renderer);

    SDL_RenderClear(state.renderer);

    gameEntities = (struct entity**)malloc(sizeof(struct entity*)*MAX_ENTITY_COUNT);

    summonEntity(0,0,0,0,50,50, 5,0,0,TAG_ENTITY + TAG_PLAYER);
    summonEntity(100,100,0,0,50,350, 0,0,0,TAG_WALL);
    summonEntity(150,400,0,0,250,50, 0,0,0,TAG_WALL);
    summonEntity(400,100,0,0,50,350, 0,0,0,TAG_WALL);
    summonEntity(230,100,0,0,170,50, 0,0,0,TAG_WALL);
    summonEntity(200,200,0,0,30,30,2,0,0,TAG_ENTITY + TAG_PLAYER_SEEKING);


    while (state.running){
        SDL_RenderClear(state.renderer);
        while (SDL_PollEvent(&state.event)){
            if (state.event.type == SDL_QUIT){
                state.running = 0;
                break;
            }
        }

        keyboardState = SDL_GetKeyboardState(NULL);

        SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
        SDL_RenderClear(state.renderer);

        SDL_SetRenderDrawColor(state.renderer,255,255,255,255);

        for (int entity = 0; entity < entityCount; entity++){
            drawEntHitbox(state.renderer,*gameEntities[entity]);

            if (gameEntities[entity]->tags & TAG_PLAYER){
                gameEntities[entity]->moveAngleRad = genPlayerMovAnglRad();
            }
            if (gameEntities[entity]->tags & TAG_PLAYER_SEEKING){
                gameEntities[entity]->moveAngleRad = atan2(gameEntities[0]->yPos-gameEntities[entity]->yPos,gameEntities[0]->xPos-gameEntities[entity]->xPos);
            }

            gameEntities[entity]->xSpeed = cos(gameEntities[entity]->moveAngleRad) * gameEntities[entity]->entSpeed;
            gameEntities[entity]->ySpeed = sin(gameEntities[entity]->moveAngleRad) * gameEntities[entity]->entSpeed;

            for (int collideEntity = 0; collideEntity < entityCount; collideEntity++){
                if (collideStatus(gameEntities[entity]->xPos + gameEntities[entity]->xSpeed,gameEntities[entity]->yPos,gameEntities[entity]->height,gameEntities[entity]->width,gameEntities[collideEntity]->xPos,gameEntities[collideEntity]->yPos,gameEntities[collideEntity]->height,gameEntities[collideEntity]->width)){
                    if (gameEntities[collideEntity]->tags & TAG_WALL){
                        gameEntities[entity]->xSpeed = 0;
                    }
                }
                if (collideStatus(gameEntities[entity]->xPos,gameEntities[entity]->yPos + gameEntities[entity]->ySpeed,gameEntities[entity]->height,gameEntities[entity]->width,gameEntities[collideEntity]->xPos,gameEntities[collideEntity]->yPos ,gameEntities[collideEntity]->height,gameEntities[collideEntity]->width)){
                    if (gameEntities[collideEntity]->tags & TAG_WALL){
                        gameEntities[entity]->ySpeed = 0;
                    }
                }
            }

            if (gameEntities[entity]->tags & TAG_PLAYER){
                if (!((keyboardState[SDL_SCANCODE_S] ^ keyboardState[SDL_SCANCODE_W]) || (keyboardState[SDL_SCANCODE_D] ^ keyboardState[SDL_SCANCODE_A]))){
                    gameEntities[entity]->xSpeed = 0;
                    gameEntities[entity]->ySpeed = 0;
                }
            }
            
            gameEntities[entity]->xPos += gameEntities[entity]->xSpeed;
            gameEntities[entity]->yPos += gameEntities[entity]->ySpeed;

        }

        printf("\r W:%d  A:%d  S:%d  D:%d",keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_A],keyboardState[SDL_SCANCODE_S],keyboardState[SDL_SCANCODE_D]);
        fflush(stdout);

        SDL_RenderPresent(state.renderer);
        SDL_Delay(16);
    }
    printf("\n");
    //entity cleanup
    for (int entity = 0; entity < entityCount; entity++){
        free(gameEntities[entity]);
    }


    free(gameEntities);

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}




void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int width, int height, float entSpeed, int faceAngleDeg, float moveAngleRad, int tags){
    gameEntities[entityCount] = (struct entity*)malloc(sizeof(struct entity));
    *gameEntities[entityCount] = (struct entity){xPos,yPos,xSpeed,ySpeed,width,height,entSpeed,faceAngleDeg,moveAngleRad,tags};
    entityCount++;
}

void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w){
    SDL_RenderDrawLineF(renderer,x,y,x+w,y);
    SDL_RenderDrawLineF(renderer,x,y,x,y+h);
    SDL_RenderDrawLineF(renderer,x+w,y+h,x+w,y);
    SDL_RenderDrawLineF(renderer,x+w,y+h,x,y+h);
}

int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W){
    return(
        (ent1X + ent1W >= ent2X)&&
        (ent1X <= ent2X + ent2W)&&
        (ent1Y + ent1H >= ent2Y)&&
        (ent1Y <= ent2Y + ent2H)
    );
}//its not unreadable, its optimized (trust)

void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity){
    drawRect(renderer,ceil(entity.xPos),ceil(entity.yPos),entity.height,entity.width);
}

float genPlayerMovAnglRad(){
    return atan2(keyboardState[SDL_SCANCODE_S]-keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_D]-keyboardState[SDL_SCANCODE_A]);
}