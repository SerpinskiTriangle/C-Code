#include "3DVertex.h"
#include <stdlib.h>

struct vertex3D *vertex3DList = NULL;
int vertex3DCount = 0;

void initVertex3DList(){
    vertex3DList = (struct vertex3D*)calloc(MAX_VERTEX_COUNT, sizeof(struct vertex3D));
}

void appendVertex3D(double x, double y, double z){
    vertex3DList[vertex3DCount].x = x;
    vertex3DList[vertex3DCount].y = y;
    vertex3DList[vertex3DCount].z = z;
    vertex3DCount++;
}

void cleanVertex3DList(){
    free(vertex3DList);
}