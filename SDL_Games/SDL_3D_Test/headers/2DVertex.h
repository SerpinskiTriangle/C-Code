#ifndef VERTEX_2D_H
#define VERTEX_2D_H
    #define MAX_VERTEX_2D_COUNT 16
    struct vertex2D {
        double x;
        double y;
    };
    extern struct vertex2D *vertex2DList;
    extern int vertex2DCount;
    void initVertex2DList();
    void appendVertex2D(double x, double y);
    void cleanVertex2DList();
#endif