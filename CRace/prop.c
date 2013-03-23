#include "prop.h"

struct Prop newProp(void)
{
    struct Prop prop;
    prop.appearance = NULL;
    prop.position=vectorZero();
    prop.direction=vectorZero();
    prop.direction.x=1;
    prop.up=vectorZero();
    prop.up.y=1;
    prop.halfSize.x = 4;
    prop.halfSize.y = 4;
    prop.halfSize.z = 4;


    return prop;
}

struct BoundingBox propBoundingBox(const struct Prop *prop)
{
    struct BoundingBox bb = newBoundingBox();
    bb.position = prop->position;
    bb.direction = prop->direction;
    bb.up = prop->up;
    bb.halfSize = prop->halfSize;

    return bb;
}

void propRestoreBoundingBox(struct Prop *prop, struct BoundingBox bb)
{
    prop->position = bb.position;
    prop->direction = bb.direction;
    prop->up = bb.up;
    prop->halfSize = bb.halfSize;
}
