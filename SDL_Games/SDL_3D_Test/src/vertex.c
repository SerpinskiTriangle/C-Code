#include "vertex.h"

struct vertex *vertexList = NULL;

void initVertexList(){
    vertexList = (struct vertex*)calloc(MAX_VERTEX_COUNT, sizeof(struct vertex));
}

void cleanVertexList(){
    free(vertexList);
}