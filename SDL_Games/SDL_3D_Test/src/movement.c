#include "movement.h"
#include "SDL_keyboardState.h"
#include "camera.h"
#include "project.h"
#include "3DVertex.h"
#include <SDL.h>
#include <math.h>

double moveSpeed = 0.5;

static struct vertex3D genMoveVector(){
    return (struct vertex3D){
    keyboardState[SDL_SCANCODE_D]-keyboardState[SDL_SCANCODE_A],
    keyboardState[SDL_SCANCODE_R]-keyboardState[SDL_SCANCODE_F],
    keyboardState[SDL_SCANCODE_W]-keyboardState[SDL_SCANCODE_S]};
}

void updatePos(double *xPos, double *yPos, double *zPos){//temporary movement system for making the rendering part of the engine
    struct vertex3D moveVector = fullRotateVertex3D(genMoveVector(),-playerCamera.angleYaw,-playerCamera.anglePitch);
    *xPos += moveSpeed*moveVector.x;
    *yPos += moveSpeed*moveVector.y;
    *zPos += moveSpeed*moveVector.z;
}

void updateRotation(double *angleYaw, double *anglePitch){
    *angleYaw   += .05*(keyboardState[SDL_SCANCODE_LEFT] - keyboardState[SDL_SCANCODE_RIGHT]);
    *anglePitch += .05*(keyboardState[SDL_SCANCODE_UP]   - keyboardState[SDL_SCANCODE_DOWN]);
}