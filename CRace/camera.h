#ifndef CAMERA_H
#define CAMERA_H
#include "common.h"
#include "vector.h"

enum CameraMode { CAMERA_MODE_FIXED, CAMERA_MODE_TPP};
struct Camera
{
    enum CameraMode mode;
    struct Vector position;
};
void cameraFollow(struct Camera* camera, struct Vector follow, struct Vector direction, double distance);

#endif /*CAMERA_H*/

