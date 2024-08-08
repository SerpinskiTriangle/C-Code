#ifndef CAMERA_H
#define CAMERA_H
    struct camera{
        double x;
        double y;
        double z;
        double angleYaw;
        double anglePitch;
    };
    extern struct camera playerCamera;
    extern int FOV;
#endif