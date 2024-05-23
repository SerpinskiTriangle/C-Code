#ifndef UTILITY_FUNCTIONS_H
    #define UTILITY_FUNCTIONS_H
    #include <SDL.h>

    #define TAG_WALL           (1 << 1)
    #define TAG_ENTITY         (1 << 2)
    #define TAG_PROJECTILE     (1 << 3)
    #define TAG_PLAYER         (1 << 4)
    #define TAG_PLAYER_SEEKING (1 << 5)
    #define TAG_QUEUED_DESTROY (1 << 6)

    #define MAX_ENTITY_COUNT 100    

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
        int index;//pointer arithmetic replacement later
        int health;
        uint8_t still;
    };

    extern struct state state;
    extern int entityCount;
    extern int destroyQueuedCount;
    extern int *allocTable;
    extern const Uint8 *keyboardState;
    extern struct entity **gameEntities;
    extern struct entity **destroyQueue;
    extern struct state state;


    void drawRect(struct SDL_Renderer *renderer, int x, int y, int h, int w);
    void drawEntHitbox(struct SDL_Renderer *renderer, struct entity entity, struct entity playerEntity);
    int collideStatus(float ent1X, float ent1Y, int ent1H, int  ent1W, float ent2X, float ent2Y, int ent2H, int ent2W);
    int collideStatusEnt(struct entity entity1,struct entity entity2);
    void summonEntity(float xPos, float yPos, float xSpeed, float ySpeed, int width, int height, float entSpeed, int faceAngleDeg, float moveAngleRad, int tags,int health);
    float genPlayerMovAnglRad();
    void destroyEntity(struct entity *entity);
    void resolveWallCollision(struct entity entity, struct entity wall);
    void queueDestroy(struct entity *entity);
    void drawGrid();
    int sign(float num);
    void accelerate(float *entSpeed, float addSpeed, float speedCap);
#endif