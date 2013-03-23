#include "vector.h"
struct Vector vectorZero(void)
{
    struct Vector result;
    result.x = 0.0;
    result.y = 0.0;
    result.z = 0.0;
    return result;
}

struct Vector vectorAdd(struct Vector a, struct Vector b)
{
    struct Vector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;
    return result;
}

struct Vector vectorSub(struct Vector a, struct Vector b)
{
    struct Vector result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

struct Vector vectorCross(struct Vector a, struct Vector b)
{
    struct Vector result;
    result.x = a.y*b.z - a.z*b.y;
    result.y = a.z*b.x - a.x*b.z;
    result.z = a.x*b.y - a.y*b.x;
    return result;
}

double vectorDot(struct Vector a, struct Vector b)
{
    return a.x*b.x + a.y*b.y +a.z*b.z;
}

struct Vector vectorTimes(struct Vector a, double b)
{
    struct Vector result;
    result.x = a.x*b;
    result.y = a.y*b;
    result.z = a.z*b;
    return result;
}

double vectorLength(struct Vector a)
{
    return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}


struct Vector vectorNormalize(struct Vector a)
{
    struct Vector result;
    double length = vectorLength(a);
    if(length < EPSILON)
        return vectorZero();
    result.x = a.x/length;
    result.y = a.y/length;
    result.z = a.z/length;
    return result;
}

struct Vector vectorRotate(double angle, struct Vector axis, struct Vector v)
{
    if(vectorLength(axis) < EPSILON) // axis is zero
    {
        return v;
    }
    double c=cos(angle);
    double s=sin(angle);
    struct Vector result;
    axis = vectorNormalize(axis);
    result.x =  (axis.x*axis.x*(1-c)+c       )*v.x +
                (axis.x*axis.y*(1-c)-axis.z*s)*v.y +
                (axis.x*axis.z*(1-c)+axis.y*s)*v.z;

    result.y =  (axis.y*axis.x*(1-c)+axis.z*s)*v.x +
                (axis.y*axis.y*(1-c)+c       )*v.y +
                (axis.y*axis.z*(1-c)-axis.x*s)*v.z;

    result.z =  (axis.z*axis.x*(1-c)-axis.y*s)*v.x +
                (axis.z*axis.y*(1-c)+axis.x*s)*v.y +
                (axis.z*axis.z*(1-c)+c       )*v.z;
    return result;

}

void vectorMulMatrixCoords(struct Vector u, struct Vector v)
{
    double m[16];
    struct Vector w = vectorCross(u ,v);
    m[0] = u.x;
    m[1] = u.y;
    m[2] = u.z;
    m[3] = 0.0;

    m[4] = v.x;
    m[5] = v.y;
    m[6] = v.z;
    m[7] = 0.0;

    m[8] = w.x;
    m[9] = w.y;
    m[10] = w.z;
    m[11] = 0.0;

    m[12] = 0.0;
    m[13] = 0.0;
    m[14] = 0.0;
    m[15] = 1.0;
    glMultMatrixd(m);
    glRotatef(-90.0,0,1,0);
}

double vectorPointPlaneDistance(struct Vector point1, struct Vector point2, struct Vector normal)
{
    normal = vectorNormalize(normal);
    double d1 = vectorDot(normal, point1);
    double d2 = vectorDot(normal, point2);
    return fabs(d1-d2);
}

