#include "checkpoint.h"

struct Checkpoint newCheckpoint(void)
{
    struct Checkpoint cp;
    cp.position = vectorZero();
    cp.direction = vectorZero();
    cp.direction.x = 1;
    return cp;
}

struct BoundingBox checkpointBoundingBox(struct Checkpoint chkpt, struct Vector halfSize)
{
    struct BoundingBox bb;
    bb.position = chkpt.position;
    bb.direction = chkpt.direction;
    bb.up = vectorZero();
    bb.up.y = 1;
    bb.halfSize = halfSize;
    return bb;
}

void checkpointRestoreBoundingBox(struct Checkpoint *chkpt, struct BoundingBox bb)
{
    chkpt->position = bb.position;
    chkpt->direction = bb.direction;
}
