#include <utility_functions.h>
#include <SDL.h>


struct state state;
int entityCount;
int *allocTable;
const Uint8 *keyboardState;
struct entity **gameEntities;
struct state state = {NULL,NULL,{0},600,600,1};

void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int width, int height, float entSpeed, int faceAngleDeg, float moveAngleRad, int tags, int health){
    gameEntities[entityCount] = (struct entity*)malloc(sizeof(struct entity));
    *gameEntities[entityCount] = (struct entity){xPos,yPos,xSpeed,ySpeed,width,height,entSpeed,faceAngleDeg,moveAngleRad,tags,entityCount,health};
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
        (ent1X + ent1W > ent2X)&&
        (ent1X < ent2X + ent2W)&&
        (ent1Y + ent1H > ent2Y)&&
        (ent1Y < ent2Y + ent2H)
    );
}//its not unreadable, its optimized (trust)
void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity, struct entity playerEntity){
    drawRect(renderer,ceil(entity.xPos)-playerEntity.xPos+state.windowWidth/2-playerEntity.width/2,ceil(entity.yPos)-playerEntity.yPos+state.windowHeight/2-playerEntity.height/2,entity.height,entity.width);
}
float genPlayerMovAnglRad(){
    return atan2(keyboardState[SDL_SCANCODE_S]-keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_D]-keyboardState[SDL_SCANCODE_A]);
}
void destroyEntity(int index){
    free(gameEntities[index]);
    if (index == entityCount){
        return;
    }
    gameEntities[index] = gameEntities[entityCount];
    gameEntities[index]->index = index;
    gameEntities[entityCount] = 0;
    entityCount--;
}
void resolveWallCollision(struct entity entity, struct entity wall){
    if (collideStatus(entity.xPos+entity.xSpeed,entity.yPos,entity.height,entity.width,wall.xPos,wall.yPos,wall.height,wall.width)){
        gameEntities[entity.index]->xSpeed = 0;
        printf("C %d-%dx",entity.index,wall.index);
    }
    if (collideStatus(entity.xPos,entity.yPos+entity.ySpeed,entity.height,entity.width,wall.xPos,wall.yPos,wall.height,wall.width)){
        gameEntities[entity.index]->ySpeed = 0;
        printf("C %d-%dy",entity.index,wall.index);
    }
}
int collideStatusEnt(struct entity entity1,struct entity entity2){
    return (collideStatus(entity1.xPos,entity1.yPos,entity1.height,entity1.width,entity2.xPos,entity2.yPos,entity2.height,entity2.width));
}