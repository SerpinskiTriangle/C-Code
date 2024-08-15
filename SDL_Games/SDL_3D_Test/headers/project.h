#ifndef PROJECT_H
#define PROJECT_H
    struct camera;
    struct vertex3D;
    struct vertex2D;

    struct vertex3D fullRotateVertex3D(struct vertex3D vertex, double angleYaw, double anglePitch);
    void fullProjectVertices(struct vertex3D *vertex3DBuffer, int vertex3DCount, struct vertex2D *vertex2DBuffer, struct camera camera);
#endif