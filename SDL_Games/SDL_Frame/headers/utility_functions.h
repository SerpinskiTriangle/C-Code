#ifndef UTILITY_FUNCTIONS_H
    #define UTILITY_FUNCTIONS_H
    #include <SDL.h>

    #define TAG_WALL           (1 << 1)
    #define TAG_ENTITY         (1 << 2)
    #define TAG_PROJECTILE     (1 << 3)
    #define TAG_PLAYER         (1 << 4)
    #define TAG_PLAYER_SEEKING (1 << 5)

    #define MAX_ENTITY_COUNT 7

    struct state {
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Event event;
        const int windowWidth;
        const int windowHeight;
        int running;
    };

    struct entity{
        float xPos;
        float yPos;
        float xSpeed;
        float ySpeed;
        int width;
        int height;
        float entSpeed;
        int faceAngleDeg;
        float moveAngleRad;
        int tags;
    };

    extern struct state state;
    extern int entityCount;
    extern int *allocTable;
    extern const Uint8 *keyboardState;
    extern struct entity **gameEntities;
    extern struct state state;

    void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w);
    void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity);
    int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W);
    void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int width, int height, float entSpeed, int faceAngleDeg, float moveAngleRad, int tags);
    float genPlayerMovAnglRad();
#endif