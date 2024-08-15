#include "project.h"
#include "3DVertex.h"
#include "2DVertex.h"
#include "camera.h"
#include <math.h>


struct vertex3D fullRotateVertex3D(struct vertex3D vertex, double angleYaw, double anglePitch){
    double yawRotatedZ = vertex.x * -sin(angleYaw) + vertex.z * cos(angleYaw);
    return (struct vertex3D){
        vertex.x * cos(angleYaw) + vertex.z * sin(angleYaw),
        vertex.y * cos(anglePitch) - (yawRotatedZ) * sin(anglePitch),
        vertex.y * sin(anglePitch) + (yawRotatedZ) * cos(anglePitch)
    };
}//this'll work trust

static struct vertex3D translateVertex(struct vertex3D vertex, double x, double y, double z){
    return (struct vertex3D){
    vertex.x-x,
    vertex.y-y,
    vertex.z-z
    };
}//i know not its not nearly as cool as the last one but we still have to

static struct vertex2D projectVertex(struct vertex3D vertex3D){//maybe useful later
    return (struct vertex2D){
    FOV*vertex3D.x/vertex3D.z, FOV*vertex3D.y/vertex3D.z
    };//yes ik z can be 0 and crash ignore that for now
}

void fullProjectVertices(struct vertex3D *vertex3DBuffer, int vertex3DCount, struct vertex2D *vertex2DBuffer, struct camera camera){//projecting only from a dedicated buffer to another dedicated buffer may be unextensible but i dont care
    for (int i = 0; i < vertex3DCount; i++){
        vertex2DBuffer[i] = projectVertex(fullRotateVertex3D(translateVertex(vertex3DBuffer[i], camera.x,camera.y,camera.z), camera.angleYaw, camera.anglePitch));
        vertex2DCount = vertex3DCount;
    }
}