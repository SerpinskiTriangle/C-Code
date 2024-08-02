#ifndef SDL_STATE_H
#define SDL_STATE_H
    struct SDL_Window;
    struct SDL_Renderer;

    extern struct SDL_state {
        struct SDL_Window* window;
        struct SDL_Renderer* renderer;
        const int windowWidth;
        const int windowHeight;
    };
    extern struct SDL_state state;    
#endif