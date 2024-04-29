#include <SDL.h>
#include <utility_functions.h>
//please for the love of christ do not actually read this, it brings me great shame but i am simply too lazy to make this pretty or safe


//one skrillion variables, very organized 
int bounceMultiplier = 10;
int paddleSpeed = 4;
const int windowHeight = 900;
const int windowWidth = 600;
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

struct rectangle{
    int xVelocity;
    int yVelocity;
    SDL_Rect rect;
};



struct rectangle rightPaddle = {0,0,{windowWidth-30,100,30,200}};
struct rectangle leftPaddle = {0,0,{1,100,30,200}};
struct rectangle ball = {9,2,{200,200,50,50}};

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
            rightPaddle.rect.y -= paddleSpeed;
            rMoveState = 1;
        }
        if (keyboardState[SDL_SCANCODE_DOWN]){
            rightPaddle.rect.y += paddleSpeed;
            rMoveState = -1;
        }
        if (keyboardState[SDL_SCANCODE_W]){
            leftPaddle.rect.y -= paddleSpeed;
            lMoveState = 1;
        }
        if (keyboardState[SDL_SCANCODE_S]){
            leftPaddle.rect.y += paddleSpeed;
            lMoveState = -1;
        }
        //yeah i dont like the if stack either but switch doesn't exactly work

        SDL_Delay(16);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        //very competent way to handle gamestate events (trust)
        if ((ball.rect.x <= leftPaddle.rect.x+leftPaddle.rect.w)&&(ball.rect.y>=leftPaddle.rect.y-ball.rect.h)&&(ball.rect.y<=leftPaddle.rect.y+leftPaddle.rect.h)){ 
            ball.xVelocity = -ball.xVelocity;
            ball.yVelocity = lMoveState*bounceMultiplier;
        }
        if ((ball.rect.x + ball.rect.w >= rightPaddle.rect.x)&&(ball.rect.y>=rightPaddle.rect.y-ball.rect.h)&&(ball.rect.y<=rightPaddle.rect.y+rightPaddle.rect.h)){
            ball.xVelocity = -ball.xVelocity;
            ball.yVelocity =  rMoveState*bounceMultiplier;
        }
        if ((ball.rect.y <= 0 )||(ball.rect.y + ball.rect.h >= windowHeight)){ 
            ball.yVelocity = -ball.yVelocity;
        }
        if (ball.rect.x<=0){
            lScore++;
            resetPos();
        }
        if (ball.rect.x>=windowWidth){
            rScore++;
            resetPos();
        }

        ball.rect.x -= ball.xVelocity;
        ball.rect.y -= ball.yVelocity;


        //render all the things! (magic numbers galore)
        renderLetter(windowWidth/2 + 20,20,lScore/10);
        renderLetter(windowWidth/2 + 20 + letterSize,20,lScore%10);

        renderLetter(windowWidth/2 - 20 -2*letterSize,20,rScore/10);
        renderLetter(windowWidth/2 - 20 - letterSize,20,rScore%10);

        SDL_RenderDrawRect(renderer,&ball.rect);
        SDL_RenderDrawRect(renderer,&leftPaddle.rect);
        SDL_RenderDrawRect(renderer,&rightPaddle.rect);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


