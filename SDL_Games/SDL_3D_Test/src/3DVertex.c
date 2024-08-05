#include "3DVertex.h"

struct vertex *vertexList = NULL;
int vertexCount = 0;

void initVertexList(){
    vertexList = (struct vertex*)calloc(MAX_VERTEX_COUNT, sizeof(struct vertex));
}

void appendVertex(double x, double y, double z){
    vertexList[vertexCount].x = x;
    vertexList[vertexCount].y = y;
    vertexList[vertexCount].z = z;
    vertexCount++;
}

void cleanVertexList(){
    free(vertexList);
}