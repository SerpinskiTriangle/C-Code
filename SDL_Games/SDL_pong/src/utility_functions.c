#include <utility_functions.h>



extern const int windowWidth;
extern const int windowHeight;
extern SDL_Renderer* renderer;
extern struct rectangle ball;
extern int digits[10][5][5];
extern int letterSize;

extern struct rectangle{
    int xVelocity;
    int yVelocity;
    SDL_Rect rect;
};

void resetPos(){ //this especially has no need to exist but i guess it's more readable
    ball.rect.x = (int)windowWidth/2;
    ball.rect.y = (int)windowHeight/2;
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

