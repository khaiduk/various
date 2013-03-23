#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include "common.h"
#include "physics.h"
#include "vector.h"

struct Checkpoint
{
    struct Vector position;
    struct Vector direction;
};

struct Checkpoint newCheckpoint(void);
struct BoundingBox checkpointBoundingBox(struct Checkpoint chkpt, struct Vector halfSize);
void checkpointRestoreBoundingBox(struct Checkpoint *chkpt, struct BoundingBox bb);


#endif/*CHECKPOINT_H*/
