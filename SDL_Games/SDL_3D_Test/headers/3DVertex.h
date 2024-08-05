#ifndef VERTEX_2D_H
#define VERTEX_2D_H
    #include <stdlib.h>
    #define MAX_VERTEX_COUNT 16
    struct vertex {
        double x;
        double y;
        double z;
    };
    extern struct vertex *vertexList;
    extern int vertexCount;
    void initVertexList();
    void appendVertex(double x, double y, double z);
    void cleanVertexList();
#endif