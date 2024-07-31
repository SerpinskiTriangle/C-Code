#include "vertex.h"

struct vertex *vertexList = NULL;

void initVertexList(){
    vertexList = (struct vertex*)malloc(sizeof(struct vertex) * MAX_VERTEX_COUNT);
}

void cleanVertexList(){
    free(vertexList);
}