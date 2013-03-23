#ifndef PROP_H
#define PROP_H

#include "vector.h"
#include "model.h"
#include "physics.h"

struct Prop
{
    struct Model* appearance;
    struct Vector position;
    struct Vector direction;
    struct Vector up;
    struct Vector halfSize;
};

struct Prop newProp(void);
struct BoundingBox propBoundingBox(const struct Prop *prop);
void propRestoreBoundingBox(struct Prop *prop, struct BoundingBox bb);

#endif /*PROP_H*/
