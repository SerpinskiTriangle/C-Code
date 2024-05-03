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

