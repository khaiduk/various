#include "camera.h"

void cameraFollow(struct Camera* camera, struct Vector follow, struct Vector direction, double distance)
{
    double h = follow.y + 5;
    struct Vector dir = vectorSub(follow, camera->position);
    dir.y = 0;
    direction = vectorNormalize(direction);
    dir.x = dir.x + 2*direction.x;
    dir.y = dir.y + 2*direction.y;
    dir.z = dir.z + 2*direction.z;
    dir = vectorNormalize(dir);
    dir = vectorTimes(dir, distance);
    camera->position = vectorSub(follow, dir);
    camera->position.y = h;

}
