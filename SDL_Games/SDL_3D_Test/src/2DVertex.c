#include "2DVertex.h"
#include <stdlib.h>

struct vertex2D *vertex2DList = NULL;
int vertex2DCount = 0;

void initVertex2DList(){
    vertex2DList = (struct vertex2D*)calloc(MAX_VERTEX_2D_COUNT, sizeof(struct vertex2D));
}

void appendVertex2D(double x, double y, double z){
    vertex2DList[vertex2DCount].x = x;
    vertex2DList[vertex2DCount].y = y;
    vertex2DCount++;
}

void cleanVertex2DList(){
    free(vertex2DList);
}