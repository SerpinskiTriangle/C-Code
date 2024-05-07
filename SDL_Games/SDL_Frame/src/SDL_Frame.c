#include <SDL.h>
#include <math.h>
#include <unistd.h>
#include <utility_functions.h>

//this looks atrocious because i want a working demo of everything before i make it scalable to innumerable entities


int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(state.windowWidth,state.windowHeight,0,&state.window,&state.renderer);

    SDL_RenderClear(state.renderer);

    gameEntities = (struct entity**)malloc(sizeof(struct entity*)*MAX_ENTITY_COUNT);
    destroyQueue = (struct entity**)malloc(sizeof(struct entity*)*MAX_ENTITY_COUNT);// :(

    summonEntity(0,0,0,0,50,50, 5,0,0,TAG_ENTITY + TAG_PLAYER,100);
    summonEntity(100,100,0,0,50,350,0,0,0,TAG_WALL,100);
    summonEntity(150,400,0,0,250,50,0,0,0,TAG_WALL,100);
    summonEntity(400,100,0,0,50,350,0,0,0,TAG_WALL,100);
    summonEntity(230,100,0,0,170,50,0,0,0,TAG_WALL,100);
    summonEntity(200,200,0,0,30,30,2,0,0,TAG_ENTITY + TAG_PLAYER_SEEKING,100);

    destroyEntity(gameEntities[5]);
    destroyEntity(gameEntities[3]);


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
            if (gameEntities[entity]->health <= 0){
                destroyEntity(gameEntities[entity]->index);
                continue;
            }
            drawEntHitbox(state.renderer,*gameEntities[entity],*gameEntities[0]);

            if (gameEntities[entity]->tags & TAG_PLAYER){
                gameEntities[entity]->moveAngleRad = genPlayerMovAnglRad();
            }
            if (gameEntities[entity]->tags & TAG_PLAYER_SEEKING){
                gameEntities[entity]->moveAngleRad = atan2(gameEntities[0]->yPos-gameEntities[entity]->yPos,gameEntities[0]->xPos-gameEntities[entity]->xPos);
            }

            gameEntities[entity]->xSpeed = cos(gameEntities[entity]->moveAngleRad) * gameEntities[entity]->entSpeed;
            gameEntities[entity]->ySpeed = sin(gameEntities[entity]->moveAngleRad) * gameEntities[entity]->entSpeed;

            for (int collideEntity = 0; collideEntity < entityCount; collideEntity++){
                if(entity == collideEntity){
                    continue;
                }
                //collision detection
                if (collideStatusEnt(*gameEntities[entity],*gameEntities[collideEntity])){
                    //if(gameEntities[entity]->tags & TAG_PROJECTILE){
                    //    destroyEntity(gameEntities[entity]->index);
                    //    gameEntities[collideEntity]->health -= 20;
                    //}
                }
                //wall collision detection happens 1 frame in the future  
                if(gameEntities[collideEntity]->tags & TAG_WALL){
                    resolveWallCollision(*gameEntities[entity],*gameEntities[collideEntity]);
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

        if (keyboardState[SDL_SCANCODE_SPACE]){
            summonEntity(gameEntities[0]->xPos+100,gameEntities[0]->yPos-100,5,5,20,20,5,0,gameEntities[0]->moveAngleRad,TAG_PROJECTILE,100);
            printf("well,");        
        }

        printf("\rW:%d  A:%d  S:%d  D:%d",keyboardState[SDL_SCANCODE_W],keyboardState[SDL_SCANCODE_A],keyboardState[SDL_SCANCODE_S],keyboardState[SDL_SCANCODE_D]);
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
    free(destroyQueue);

    SDL_DestroyRenderer(state.renderer);
    SDL_DestroyWindow(state.window);
    SDL_Quit();
    return 0;
}

