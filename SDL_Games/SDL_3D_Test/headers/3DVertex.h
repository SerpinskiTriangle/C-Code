#ifndef VERTEX_3D_H
#define VERTEX_3D_H
    #define MAX_VERTEX_3D_COUNT 16
    struct vertex3D {
        double x;
        double y;
        double z;
    };
    extern struct vertex3D *vertex3DList;
    extern int vertex3DCount;
    void initVertex3DList();
    void appendVertex3D(double x, double y, double z);
    void cleanVertex3DList();
#endif