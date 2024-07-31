#ifndef VERTEX_H
#define VERTEX_H
    #include <stdlib.h>
    #define MAX_VERTEX_COUNT 16
    struct vertex {
        double x;
        double y;
        double z;
    };
    extern struct vertex *vertexList;
    void initVertexList();
    void cleanVertexList();
#endif