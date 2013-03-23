#ifndef VECTOR_H
#define VECTOR_H

#include "common.h"
struct Vector
{
    double x;
    double y;
    double z;
};

struct Vector vectorZero(void);
struct Vector vectorAdd(struct Vector a, struct Vector b);
struct Vector vectorSub(struct Vector a, struct Vector b);
struct Vector vectorCross(struct Vector a, struct Vector b);
double vectorDot(struct Vector a, struct Vector b);
struct Vector vectorTimes(struct Vector a, double b);
double vectorLength(struct Vector a);
struct Vector vectorNormalize(struct Vector a);
struct Vector vectorRotate(double angle, struct Vector axis, struct Vector v);
void vectorMulMatrixCoords(struct Vector u, struct Vector v);
double vectorPointPlaneDistance(struct Vector point1, struct Vector point2, struct Vector normal);

#endif /*VECTOR_H*/
