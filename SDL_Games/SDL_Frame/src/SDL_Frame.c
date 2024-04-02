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
}EG;


struct entity player = {0,0,0,0,playerHeight, playerWidth,0,0};
struct entity test = {300,300,0,0,100,100,0,0};

struct entity ***gameEntities[CLASS_COUNT];

int allocTable[CLASS_COUNT][1] = {
    {0}, //walls
    {0}, //entities
    {0}  //projectiles
};

/* ok please dont laugh i promise this is for memory efficiency
 * all entities are in a hierarchy (class > type > individual entity)
 * 1 type per class for now (pointers will be implemented later for different numbers of types for each class)(i think)
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
        gameEntities[i] = (struct entity***)malloc(sizeof(struct entity**));
        for (int j = 0; j <= 5; j++){
            *gameEntities[i] = (struct entity**)malloc(sizeof(struct entity*) * MAX_ENTITIES);
        }
    }


    //we love castin spells
    summonEntity(100,100,0,0,350,50,0,0,0,0);
    summonEntity(400,100,0,0,350,50,0,0,1,0);
    summonEntity(150,400,0,0,50,250,0,0,1,0);
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

        
        for(int class = 0; class <= CLASS_COUNT - 1; class++){
            for(int entity = 0; entity < allocTable[class][0]; entity++){
                drawEntHitbox(state.renderer,*gameEntities[class][0][entity]);
            }
        }
        
        //drawEntHitbox(state.renderer,*gameEntities[0][0][0]);
        drawEntHitbox(state.renderer,player);
        drawEntHitbox(state.renderer,test);
        SDL_RenderPresent(state.renderer);
        SDL_Delay(16);
        
        frame++;
    }
    //entity cleanup
    
    for(int class = 0; class <= CLASS_COUNT - 1; class++){
        for(int entity = 0; entity < allocTable[class][0]; entity++){
            free(gameEntities[class][0][entity]);
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