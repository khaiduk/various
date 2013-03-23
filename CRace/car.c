#include "car.h"

struct CarPrototype newCarPrototype(void)
{
    struct CarPrototype cp;
    cp.halfSize = vectorZero();
    cp.wheelsPos = vectorZero();
    return cp;
}

struct Car newCar(struct CarPrototype proto)
{
    int i;
    struct Car car;
    car.throttle=0.0;
    car.turn=0.0;
    car.wheelAngle = 0.0;
    car.wheelRotate = 0.0;
    car.brake = FALSE;
    car.position=vectorZero();
    car.position.y=2;
    car.direction=vectorZero();
    car.direction.x=1;
    car.up=vectorZero();
    car.up.y=1;
    car.velocity=vectorZero();
    car.angularVelocity=vectorZero();
    car.force=vectorZero();
    car.torque=vectorZero();
    car.mass = 750;
    car.halfSize = proto.halfSize;

    car.raceTime = 0.0;
    car.currentTime = 0.0;
    car.bestTime = 0.0;
    car.lap = 1;
    car.nextCheckpoint = 0;
    car.lastBoundingBox = carBoundingBox(&car);

    for(i=0;i<WHEELS_NUM;i++)
    {
        car.wheels[i].offset = vectorZero();
        car.wheels[i].offset.y = proto.wheelsPos.y;
        switch(i)
        {
            case 0: case 1: car.wheels[i].offset.x = proto.wheelsPos.x; break;
            case 2: case 3: car.wheels[i].offset.x = -proto.wheelsPos.x; break;
        }
        switch(i)
        {
            case 0: case 2: car.wheels[i].offset.z = proto.wheelsPos.z; car.wheels[i].drive = TRUE; break;
            case 1: case 3: car.wheels[i].offset.z = -proto.wheelsPos.z; car.wheels[i].drive = FALSE;break;
        }
    }

    return car;
}

void carZeroForce(struct Car *car)
{
    car->force = vectorZero();
    car->torque = vectorZero();
}

/* Note: vectors in world frame of reference */
void carApplyForce(struct Car *car, struct Vector force, struct Vector offset)
{
    car->force = vectorAdd(car->force, force);
    car->torque = vectorAdd(car->torque, vectorCross(offset, force));
}

//render in right position and orientation
void carRender(const struct Car *car, const struct Model *carAppearance, const struct Model *wheelAppearance)
{
    int i;

    glPushMatrix();
    glTranslatef(car->position.x,car->position.y,car->position.z);
    vectorMulMatrixCoords(car->direction, car->up);

    modelDisplay(carAppearance);

    for(i=0;i<WHEELS_NUM;i++)
    {
        double ypos = -car->position.y + car->wheels[i].ypos;
        if(ypos<-2) ypos = -2;
        glPushMatrix();
        glTranslatef(car->wheels[i].offset.x, ypos,car->wheels[i].offset.z);
        if(!car->wheels[i].drive)
            glRotatef(car->wheelAngle*300,0,1,0);
        glRotatef(-car->wheelRotate,1,0,0);
        modelDisplay(wheelAppearance);
        glPopMatrix();
    }

    glPopMatrix();

}

struct BoundingBox carBoundingBox(const struct Car *car)
{
    struct BoundingBox bb = newBoundingBox();
    bb.position = car->position;
    bb.direction = car->direction;
    bb.up = car->up;
    bb.halfSize = car->halfSize;

    return bb;
}

void carRestoreBoundingBox(struct Car *car, struct BoundingBox bb)
{
    car->position = bb.position;
    car->direction = bb.direction;
    car->up = bb.up;
}
