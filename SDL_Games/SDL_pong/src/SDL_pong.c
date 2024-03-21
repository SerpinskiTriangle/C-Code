#include <SDL.h>
//please for the love of christ do not actually read this, it brings me great shame but i am simply too lazy to make this pretty or safe


//one skrillion variables, very organized (i didn't wanna use structs)   
int xVelocity = 12;
int yVelocity = 8;
int paddleSpeed = 5;
int bounceMultiplier = 10;
const int windowHeight = 900;
const int windowWidth = 600;
SDL_Rect rect = {200,200,50,50};
SDL_Rect leftPaddle = {1,100,30,200};
SDL_Rect rightPaddle = {windowWidth-30,100,30,200};
SDL_Event event;
int lMoveState = 0;
int rMoveState = 0;
int lScore = 0;
int rScore = 0;
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
const Uint8 *keyboardState;
int running = 1;
int letterSize = 50 ;

int digits[10][5][5] = {
    {
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
    {
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 1, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1},
    },
    {
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
    {
        {0, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 0, 1, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 0},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 1, 0, 0, 0}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
    {
        {0, 1, 1, 1, 1},
        {0, 1, 0, 0, 1},
        {0, 1, 1, 1, 1},
        {0, 0, 0, 0, 1},
        {0, 1, 1, 1, 1}
    },
};

//these dont need to exist but i wanted to encapsulate anyway
void resetPos();
void renderLetter(int x, int y, int digit);
void drawRect(int x, int y, int h, int w);

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(windowWidth,windowHeight,0,&window,&renderer);

    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    
    while (running) {
        if (lScore == 100||rScore == 100){
            break;
        }
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                running = 0;
                break;
            }
        }
        lMoveState = 0;
        rMoveState = 0;
        keyboardState = SDL_GetKeyboardState(NULL);

        if (keyboardState[SDL_SCANCODE_UP]){
            rightPaddle.y -= paddleSpeed;
            rMoveState = 1;
        }
        if (keyboardState[SDL_SCANCODE_DOWN]){
            rightPaddle.y += paddleSpeed;
            rMoveState = -1;
        }
        if (keyboardState[SDL_SCANCODE_W]){
            leftPaddle.y -= paddleSpeed;
            lMoveState = 1;
        }
        if (keyboardState[SDL_SCANCODE_S]){
            leftPaddle.y += paddleSpeed;
            lMoveState = -1;
        }
        //yeah i dont like the if stack either but switch doesn't exactly work

        SDL_Delay(16);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        //very competent way to handle gamestate events (trust)
        if ((rect.x <= leftPaddle.x+leftPaddle.w)&&(rect.y>=leftPaddle.y-rect.h)&&(rect.y<=leftPaddle.y+leftPaddle.h)){ 
            xVelocity = -xVelocity;
            yVelocity = lMoveState*bounceMultiplier;
        }
        if ((rect.x + rect.w >= rightPaddle.x)&&(rect.y>=rightPaddle.y-rect.h)&&(rect.y<=rightPaddle.y+rightPaddle.h)){
            xVelocity = -xVelocity;
            yVelocity =  rMoveState*bounceMultiplier;
        }
        if ((rect.y <= 0 )||(rect.y + rect.h >= windowHeight)){ 
            yVelocity = -yVelocity;
        }
        if (rect.x<=0){
            lScore++;
            resetPos();
        }
        if (rect.x>=windowWidth){
            rScore++;
            resetPos();
        }

        rect.x -= xVelocity;
        rect.y -= yVelocity;


        //render all the things! (magic numbers galore)
        renderLetter(windowWidth/2 + 20,20,lScore/10);
        renderLetter(windowWidth/2 + 20 + letterSize,20,lScore%10);

        renderLetter(windowWidth/2 - 20 -2*letterSize,20,rScore/10);
        renderLetter(windowWidth/2 - 20 - letterSize,20,rScore%10);

        SDL_RenderDrawRect(renderer,&rect);
        SDL_RenderDrawRect(renderer,&leftPaddle);
        SDL_RenderDrawRect(renderer,&rightPaddle);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


void resetPos(){ //this especially has no need to exist but i guess it's more readable
    rect.x = (int)windowWidth/2;
    rect.y = (int)windowHeight/2;
}


void drawRect(int x, int y, int h, int w){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    for (int i = 0; i <= w; i++){
        for (int j = 0; j <= h; j++){
            SDL_RenderDrawPoint(renderer, x + i, y + j);
        }
    }
}


void renderLetter(int xAdj, int yAdj, int digit){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    for (int i = 0; i <=4; i++){
        for (int j = 0; j <=4; j++){
            if (digits[digit][j][i]){
                drawRect(xAdj+i*letterSize/5,yAdj+j*letterSize/5,letterSize/5,letterSize/5);
            }
        }
    }
}
