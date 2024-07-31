#ifndef SDL_STATE_H
#define SDL_STATE_H
    #include <SDL.h>
    
    extern struct SDL_state {
        SDL_Window* window;
        SDL_Renderer* renderer;
        const int windowWidth;
        const int windowHeight;
    };
#endif