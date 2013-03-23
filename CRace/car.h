#ifndef CAR_H
#define CAR_H

#include "common.h"
#include "vector.h"
#include "model.h"
#include "physics.h"
#include "terrain.h"

#define WHEELS_NUM 4

struct Wheel
{
    struct Vector offset;
    double ypos;
    BOOL drive; //is drive wheel (TRUE) or steering wheel (FALSE)
};

struct CarPrototype
{
    struct Vector halfSize;
    struct Vector wheelsPos;
};

struct Car
{
    double throttle;
    double turn;
    double wheelAngle;
    double wheelRotate;
    BOOL brake;

    struct Vector position;
    struct Vector direction;
    struct Vector up;

    struct Vector velocity;
    struct Vector angularVelocity;/* pseudovector*/

    struct Vector force; /* net force */
    struct Vector torque;/* pseudovector*/

    float mass;
    struct Vector halfSize;

    double raceTime;
    double currentTime;
    double bestTime;
    int lap;
    int nextCheckpoint;

    struct BoundingBox lastBoundingBox;

    struct Wheel wheels[WHEELS_NUM];
};

struct CarPrototype newCarPrototype(void);
struct Car newCar(struct CarPrototype proto);
void carZeroForce(struct Car *car);
void carApplyForce(struct Car *car, struct Vector force, struct Vector offset);
void carRender(const struct Car *car, const struct Model *carAppearance, const struct Model *wheelAppearance);
struct BoundingBox carBoundingBox(const struct Car *car);
void carRestoreBoundingBox(struct Car *car, struct BoundingBox bb);
#endif /*CAR_H*/
