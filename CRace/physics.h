#ifndef PHYSICS_H
#define PHYSICS_H
#include "common.h"
#include "vector.h"

/*

     ^ z
     |  /^ y
     | /
     |/_____> x

     +-------------------+-------------------+
     |                   |                   |
     |               halfSize.z              |
     |                   |                   |
     |                   +----halfSize.x-----+  ---direction-->
     |               __-^                    |
     |         position                      |  (*) up
     |       __--                            |
     +---__----------------------------------+
    __--
__--
*/
struct BoundingBox
{
    struct Vector position;
    struct Vector direction;
    struct Vector up;
    struct Vector halfSize;
};

struct BoundingBox newBoundingBox(void);
struct BoundingBox boundingBoxInterpolate(const struct BoundingBox *a, const struct BoundingBox *b);
void boundingBoxGetVerticles(struct Vector *verticles, const struct BoundingBox *bb);
void boundingBoxRender(const struct BoundingBox *bb);
double boundingBoxSeparationTest(struct Vector L, struct BoundingBox a, struct BoundingBox b);
BOOL boundingBoxCollide(struct BoundingBox a, struct BoundingBox b);
void boundingBoxCollisionPoint(struct Vector* normal, struct Vector* point, struct BoundingBox ai, struct BoundingBox bi, struct BoundingBox af, struct BoundingBox bf);
#endif /*PHYSICS_H*/
