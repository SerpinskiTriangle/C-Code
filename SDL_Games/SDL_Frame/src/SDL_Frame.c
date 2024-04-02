#include <SDL.h>
#include <math.h>
#include <unistd.h>

//this looks atrocious because i want a working demo of everything before i make it scalable to innumerable entities

#define CLASS_COUNT 3
#define MAX_ENTITIES 5



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


struct entity ***gameEntities[CLASS_COUNT];

int allocTable[CLASS_COUNT][2] = {//will be an arr of pointers (mentioned later)
    {0,0}, //walls
    {0,0}, //entities
    {0,0}  //projectiles
};

/* ok please dont laugh i promise this is for memory efficiency
 * all entities are in a hierarchy (class > type > individual entity)
 * 2 types per class for now (pointers will be implemented later for different numbers of types for each class)(i think)
 * allocTable holds the amount of entity pointers for each type for each class
 * new pointers to entities will always be placed at that index
 */




void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w);

int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W);

void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int height, int width, int faceAngleDeg, float moveAngleRad, int class, int type){
    struct entity *entity = (struct entity*)malloc(sizeof(struct entity));
    *entity = (struct entity){xPos,yPos,xSpeed,ySpeed,height,width,faceAngleDeg,moveAngleRad};
    gameEntities[class][type][allocTable[class][type]] = entity;
    allocTable[class][type]++;
}

void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity);


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(state.windowWidth,state.windowHeight,0,&state.window,&state.renderer);

    SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
    SDL_RenderClear(state.renderer);

    for (int i = 0; i <= CLASS_COUNT - 1; i++){
        gameEntities[i] = (struct entity***)malloc(sizeof(struct entity**)*2);
        for (int j = 0; j <= 1; j++){
            *(gameEntities[i]+j) = (struct entity**)malloc(sizeof(struct entity*) * MAX_ENTITIES);
        }
    }


    //we love castin spells
    summonEntity(0,0,0,0,50,50,0,0,1,0);//player
    summonEntity(100,100,0,0,350,50,0,0,0,0);
    summonEntity(400,100,0,0,350,50,0,0,0,0);
    summonEntity(150,400,0,0,50,250,0,0,0,0);
    summonEntity(210,100,0,0,50,190,0,0,0,0);
    summonEntity(300,300,0,0,10,10,0,0,0,0);
    summonEntity(200,200,0.1,0.3,30,30,0,0,1,1);//test little guy
    while (state.running){
        SDL_SetRenderDrawColor(state.renderer,0,0,0,255);
        SDL_RenderClear(state.renderer);
        while (SDL_PollEvent(&state.event)){
            if (state.event.type == SDL_QUIT){
                state.running = 0;
                break;
            }
        }

        for (int entity = 0; entity < allocTable[1][1]; entity++){//player-seeking logic
            gameEntities[1][1][entity]->moveAngleRad = atan2(gameEntities[1][0][0]->yPos-gameEntities[1][1][entity]->yPos,gameEntities[1][0][0]->xPos-gameEntities[1][1][entity]->xPos);
            
            gameEntities[1][1][entity]->xSpeed = cos(gameEntities[1][1][entity]->moveAngleRad) /2;
            gameEntities[1][1][entity]->ySpeed = sin(gameEntities[1][1][entity]->moveAngleRad) /2;
        }
        
        keyboardState = SDL_GetKeyboardState(NULL);
        if (!(keyboardState[SDL_SCANCODE_W] - keyboardState[SDL_SCANCODE_S] || keyboardState[SDL_SCANCODE_A] - keyboardState[SDL_SCANCODE_D])){
            still = 1;
            gameEntities[1][0][0]->xSpeed = 0;
            gameEntities[1][0][0]->ySpeed = 0;
        }
        else {
            gameEntities[1][0][0]->moveAngleRad = atan2(keyboardState[SDL_SCANCODE_S] - keyboardState[SDL_SCANCODE_W], keyboardState[SDL_SCANCODE_D] - keyboardState[SDL_SCANCODE_A]);
            
            gameEntities[1][0][0]->xSpeed = cos(gameEntities[1][0][0]->moveAngleRad);
            gameEntities[1][0][0]->ySpeed = sin(gameEntities[1][0][0]->moveAngleRad);
        }//quite silly indeed

        

        for (int type = 0; type <= 1; type++){//collision detection + resolution
            for (int entity = 0; entity < allocTable[1][type]; entity++){
                for (int wall = 0; wall < allocTable[0][0]; wall++){
                    if (collideStatus(gameEntities[1][type][entity]->xPos+gameEntities[1][type][entity]->xSpeed*5,gameEntities[1][type][entity]->yPos,gameEntities[1][type][entity]->height,gameEntities[1][type][entity]->width,gameEntities[0][0][wall]->xPos,gameEntities[0][0][wall]->yPos,gameEntities[0][0][wall]->height,gameEntities[0][0][wall]->width)){
                        gameEntities[1][type][entity]->xSpeed = 0;
                    }
                    if (collideStatus(gameEntities[1][type][entity]->xPos,gameEntities[1][type][entity]->yPos+gameEntities[1][type][entity]->ySpeed*5,gameEntities[1][type][entity]->height,gameEntities[1][type][entity]->width,gameEntities[0][0][wall]->xPos,gameEntities[0][0][wall]->yPos,gameEntities[0][0][wall]->height,gameEntities[0][0][wall]->width)){
                        gameEntities[1][type][entity]->ySpeed = 0;
                    }
                }
            }
        }


        

        for (int class = 0; class < CLASS_COUNT; class++){//the walls will be able to move if i so will it
            for (int type = 0; type < 2; type++){//proper (non-magic-number) implementation later
                for (int entity = 0; entity < allocTable[class][type]; entity++){
                    gameEntities[class][type][entity]->xPos += gameEntities[class][type][entity]->xSpeed * 5;
                    gameEntities[class][type][entity]->yPos += gameEntities[class][type][entity]->ySpeed * 5;
                }
            }
        }
        //gameEntities[1][0][0]->xPos += 5 * gameEntities[1][0][0]->xSpeed;
        //gameEntities[1][0][0]->yPos += 5 * gameEntities[1][0][0]->ySpeed;
        //debug section
        printf("\rMovAng/pi: %-+6f xSpeed: %-+6f ySpeed: %-+6f scnW: %d scnA: %d scnS: %d scnD: %d",gameEntities[1][0][0]->moveAngleRad / 3.1415926,gameEntities[1][0][0]->xSpeed*5,gameEntities[1][0][0]->ySpeed*5,keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_A],keyboardState[SDL_SCANCODE_S],keyboardState[SDL_SCANCODE_D]);
        fflush(stdout);


        SDL_SetRenderDrawColor(state.renderer,255,255,255,255);

        
        for(int class = 0; class <= CLASS_COUNT - 1; class++){
            for (int type = 0; type <= 1; type++){
                for(int entity = 0; entity < allocTable[class][type]; entity++){
                    drawEntHitbox(state.renderer,*gameEntities[class][type][entity]);
                }
            }
        }

        SDL_RenderPresent(state.renderer);
        SDL_Delay(16);
        
        frame++;    }
    //entity cleanup
    
    for(int class = 0; class <= CLASS_COUNT - 1; class++){
        for (int type = 0; type <= 1; type++){
            for(int entity = 0; entity < allocTable[class][type]; entity++){
                free(gameEntities[class][type][entity]);
            }
        }
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

void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity){
    drawRect(renderer,entity.xPos,entity.yPos,entity.height,entity.width);
}