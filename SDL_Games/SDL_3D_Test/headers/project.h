#ifndef PROJECT_H
#define PROJECT_H
    struct camera;
    struct vertex3D;
    struct vertex2D;
    
    struct vertex3D rotateVertex(struct vertex3D vertex, double angleYaw, double anglePitch);
    struct vertex3D translateVertex(struct vertex3D vertex, double x, double y, double z);
    void fullProjectVertices(struct vertex3D *vertex3DBuffer, int vertex3DCount, struct vertex2D *vertex2DBuffer, struct camera camera);
#endif