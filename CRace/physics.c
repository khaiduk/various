#include "physics.h"

struct BoundingBox newBoundingBox(void)
{
    struct BoundingBox bb;
    bb.position = vectorZero();
    bb.direction = vectorZero();
    bb.direction.x = 1;
    bb.up = vectorZero();
    bb.up.y = 1;
    bb.halfSize.x = 1;
    bb.halfSize.y = 1;
    bb.halfSize.z = 1;
    return bb;
}

struct BoundingBox boundingBoxInterpolate(const struct BoundingBox *a, const struct BoundingBox *b)
{
    struct BoundingBox bb;
    bb.position = vectorTimes( vectorAdd(a->position, b->position), 0.5 );
    bb.direction = vectorNormalize(vectorAdd(a->direction, b->direction));
    bb.up = vectorNormalize(vectorAdd(a->up, b->up));
    bb.halfSize = vectorTimes( vectorAdd(a->halfSize, b->halfSize), 0.5 );
    return bb;
}

//verticles in global frame of reference
void boundingBoxGetVerticles(struct Vector *verticles, const struct BoundingBox *bb)
{
    verticles[0]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), bb->halfSize.z)
                           )));
    verticles[1]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, -bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), bb->halfSize.z)
                           )));
    verticles[2]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, -bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, -bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), bb->halfSize.z)
                           )));
    verticles[3]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, -bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), bb->halfSize.z)
                           )));
    verticles[4]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), -bb->halfSize.z)
                           )));
    verticles[5]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, -bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), -bb->halfSize.z)
                           )));
    verticles[6]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, -bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, -bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), -bb->halfSize.z)
                           )));
    verticles[7]=vectorAdd(bb->position,
                 vectorAdd( vectorTimes(bb->direction, bb->halfSize.x),
                 vectorAdd( vectorTimes(bb->up, -bb->halfSize.y),
                            vectorTimes( vectorCross(bb->up, bb->direction), -bb->halfSize.z)
                           )));
}

void boundingBoxRender(const struct BoundingBox *bb)
{
    struct Vector verticles[8];
    boundingBoxGetVerticles(verticles, bb);


    glBegin(GL_LINES);
        glVertex3f(verticles[0].x, verticles[0].y, verticles[0].z);
        glVertex3f(verticles[1].x, verticles[1].y, verticles[1].z);

        glVertex3f(verticles[1].x, verticles[1].y, verticles[1].z);
        glVertex3f(verticles[2].x, verticles[2].y, verticles[2].z);

        glVertex3f(verticles[2].x, verticles[2].y, verticles[2].z);
        glVertex3f(verticles[3].x, verticles[3].y, verticles[3].z);

        glVertex3f(verticles[3].x, verticles[3].y, verticles[3].z);
        glVertex3f(verticles[0].x, verticles[0].y, verticles[0].z);
        //
        glVertex3f(verticles[4].x, verticles[4].y, verticles[4].z);
        glVertex3f(verticles[5].x, verticles[5].y, verticles[5].z);

        glVertex3f(verticles[5].x, verticles[5].y, verticles[5].z);
        glVertex3f(verticles[6].x, verticles[6].y, verticles[6].z);

        glVertex3f(verticles[6].x, verticles[6].y, verticles[6].z);
        glVertex3f(verticles[7].x, verticles[7].y, verticles[7].z);

        glVertex3f(verticles[7].x, verticles[7].y, verticles[7].z);
        glVertex3f(verticles[4].x, verticles[4].y, verticles[4].z);
        //
        glVertex3f(verticles[0].x, verticles[0].y, verticles[0].z);
        glVertex3f(verticles[4].x, verticles[4].y, verticles[4].z);

        glVertex3f(verticles[1].x, verticles[1].y, verticles[1].z);
        glVertex3f(verticles[5].x, verticles[5].y, verticles[5].z);

        glVertex3f(verticles[2].x, verticles[2].y, verticles[2].z);
        glVertex3f(verticles[6].x, verticles[6].y, verticles[6].z);

        glVertex3f(verticles[3].x, verticles[3].y, verticles[3].z);
        glVertex3f(verticles[7].x, verticles[7].y, verticles[7].z);
    glEnd();
}

/*            ,'.
           /   `.
         ,'      `-.
       ,'           `.
     ,'              /`.
    /              ,'   `.
  ,'              /       `-.
,'              ;:           `.
.                |`.         ,.-:
 `-.             |  `-.       //|
    `.           |     `. . ,'  |
      `.         |       :\/    |
        `-.      |       ,'     |
           `.    |      / |     |
             `.  |    ,'  |     |
               `-|   /    |     |
                 |`,'     |     |
                 |        |     |
_________________|________|_____|________
                 |        |     |
                 |        |     |
                 |<------>|     |
                   |x*L|  |     |    ..
                        + |     |  = |_\
                          |<--->|    | \
                           |y*L|        0


                     _              `.
                _,,-"\             /  `-.
          __,-""      \           /      `.
     _,,-"             \         /         `-.
  +-"        |          \_      /             `.
   \         |      _,,-"+     /        |       `-.
    \        | _,,-"     | s  |-.       |        /
     \    _,,+"          | e  |  `-.    |       /
      ,,-"   |           | p  |     `-. |     ,'
             |           | a  |        `+.   /
             |           | r  |         | `-/
             |           | a  |         |
             |<--R0----->| t  |<---R1-->|
-------------+-----------+-i--+---------+----------
             |             o            |
             |             n            |
             |      R                   |
             |<------------------------>|
*/

/* Returns Positive on separation - gives distance*/
double boundingBoxSeparationTest(struct Vector L, struct BoundingBox a, struct BoundingBox b)
{
    double R = fabs(vectorDot(L, vectorSub(a.position, b.position)));
    double R0 = a.halfSize.x*fabs(vectorDot(L, a.direction)) +
                a.halfSize.y*fabs(vectorDot(L, a.up)) +
                a.halfSize.z*fabs(vectorDot(L, vectorCross(a.up, a.direction)));
    double R1 = b.halfSize.x*fabs(vectorDot(L, b.direction)) +
                b.halfSize.y*fabs(vectorDot(L, b.up)) +
                b.halfSize.z*fabs(vectorDot(L, vectorCross(b.up, b.direction)));
    return R - (R0 + R1);
}

BOOL boundingBoxCollide(struct BoundingBox a, struct BoundingBox b)
{
    struct Vector a1 = a.direction = vectorNormalize(a.direction);
    struct Vector a2 = a.up = vectorNormalize(a.up);
    struct Vector a3 = vectorCross(a1, a2);
    struct Vector b1 = b.direction = vectorNormalize(b.direction);
    struct Vector b2 = b.up = vectorNormalize(b.up);
    struct Vector b3 = vectorCross(b1, b2);

    if(boundingBoxSeparationTest(a1, a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(a2, a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(a3, a, b)>0) return FALSE;

    if(boundingBoxSeparationTest(b1, a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(b2, a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(b3, a, b)>0) return FALSE;

    if(boundingBoxSeparationTest(vectorCross(a1, b1), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a1, b2), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a1, b3), a, b)>0) return FALSE;

    if(boundingBoxSeparationTest(vectorCross(a2, b1), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a2, b2), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a2, b3), a, b)>0) return FALSE;

    if(boundingBoxSeparationTest(vectorCross(a3, b1), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a3, b2), a, b)>0) return FALSE;
    if(boundingBoxSeparationTest(vectorCross(a3, b3), a, b)>0) return FALSE;

    return TRUE;
}

void boundingBoxCollisionPoint(struct Vector* normal, struct Vector* point, struct BoundingBox ai, struct BoundingBox bi, struct BoundingBox af, struct BoundingBox bf)
{
    int i;
    int separartingAxesNum = 0;
    int lastSeparartingAxis = 0;
    struct BoundingBox a;
    struct BoundingBox b;
    double distance, minDistance;
    i=1000;
    while(separartingAxesNum != 1 && i-->0)
    {
        separartingAxesNum = 0;
        a = boundingBoxInterpolate(&ai, &af);
        b = boundingBoxInterpolate(&bi, &bf);

        struct Vector a1 = a.direction = vectorNormalize(a.direction);
        struct Vector a2 = a.up = vectorNormalize(a.up);
        struct Vector a3 = vectorCross(a1, a2);
        struct Vector b1 = b.direction = vectorNormalize(b.direction);
        struct Vector b2 = b.up = vectorNormalize(b.up);
        struct Vector b3 = vectorCross(b1, b2);

        if(boundingBoxSeparationTest(a1, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=0;}
        if(boundingBoxSeparationTest(a2, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=1;}
        if(boundingBoxSeparationTest(a3, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=2;}

        if(boundingBoxSeparationTest(b1, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=3;}
        if(boundingBoxSeparationTest(b2, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=4;}
        if(boundingBoxSeparationTest(b3, a, b)>0) {separartingAxesNum++; lastSeparartingAxis=5;}

        if(boundingBoxSeparationTest(vectorCross(a1, b1), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=6;}
        if(boundingBoxSeparationTest(vectorCross(a1, b2), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=7;}
        if(boundingBoxSeparationTest(vectorCross(a1, b3), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=8;}

        if(boundingBoxSeparationTest(vectorCross(a2, b1), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=9;}
        if(boundingBoxSeparationTest(vectorCross(a2, b2), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=10;}
        if(boundingBoxSeparationTest(vectorCross(a2, b3), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=11;}

        if(boundingBoxSeparationTest(vectorCross(a3, b1), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=12;}
        if(boundingBoxSeparationTest(vectorCross(a3, b2), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=13;}
        if(boundingBoxSeparationTest(vectorCross(a3, b3), a, b)>0) {separartingAxesNum++; lastSeparartingAxis=14;}

        if(separartingAxesNum>1) // is not colliding yet
        {
            ai = a;
            bi = b;
        }
        if(separartingAxesNum<1) // is already colliding
        {
            af = a;
            bf = b;
        }
    }

    if(lastSeparartingAxis<6) // face-vertex
    {
        struct Vector center;
        int pointId = 0;
        struct Vector verticles[6];
        if(lastSeparartingAxis<3) // b-vertex collide with a-face
        {
            boundingBoxGetVerticles(verticles, &b);
            center = a.position;
        }
        else // a-vertex collide with b-face
        {
            boundingBoxGetVerticles(verticles, &a);
            center = b.position;
        }

        switch(lastSeparartingAxis)
        {
            case 0:
                *normal = a.direction;
                distance = a.halfSize.x;
                break;
            case 1:
                *normal = a.up;
                distance = a.halfSize.y;
                break;
            case 2:
                *normal = vectorCross(a.direction, a.up);
                distance = a.halfSize.z;
                break;
            case 3:
                *normal = b.direction;
                distance = b.halfSize.x;
                break;
            case 4:
                *normal = b.up;
                distance = b.halfSize.y;
                break;
            case 5:
                *normal = vectorCross(b.direction, b.up);;
                distance = b.halfSize.z;
                break;
            default:
                *normal = vectorZero();
                distance = 0;
        }

        minDistance = -1;
        for(i=0;i<6;i++)
        {
            distance = vectorPointPlaneDistance(verticles[i], center, *normal);
            if(minDistance < 0 || distance < minDistance)
            {
                minDistance = distance;
                pointId = i;
            }

        }

        *point = verticles[pointId];
    }
    else // edge-edge
    {
        struct Vector a1 = a.direction = vectorNormalize(a.direction);
        struct Vector a2 = a.up = vectorNormalize(a.up);
        struct Vector a3 = vectorNormalize( vectorCross(a1, a2) );
        struct Vector b1 = b.direction = vectorNormalize(b.direction);
        struct Vector b2 = b.up = vectorNormalize(b.up);
        struct Vector b3 = vectorNormalize(vectorCross(b1, b2));

        struct Vector halfEdgeA, halfEdgeB;
        struct Vector halfOffsetA[4];
        struct Vector halfOffsetB[4];
        for(i=0;i<4;i++)
        {switch(lastSeparartingAxis)
        {
                case 6: case 7: case 8:
                    halfEdgeA = vectorTimes(a1, a.halfSize.x);
                    halfOffsetA[i] = vectorAdd( vectorTimes(a1, 0),
                                  vectorAdd( vectorTimes(a2, a.halfSize.y * (1-2*(i%2)) ),
                                             vectorTimes(a3, a.halfSize.z * (i>=2 ? -1 : 1) )));
                    break;
                case 9: case 10: case 11:
                    halfEdgeA = vectorTimes(a2, a.halfSize.y);
                    halfOffsetA[i] = vectorAdd( vectorTimes(a1, a.halfSize.x * (1-2*(i%2))),
                                  vectorAdd( vectorTimes(a2, 0),
                                             vectorTimes(a3, a.halfSize.z * (i>=2 ? -1 : 1))));
                    break;
                case 12: case 13: case 14:
                    halfEdgeA = vectorTimes(a3, a.halfSize.z);
                    halfOffsetA[i] = vectorAdd( vectorTimes(a1, a.halfSize.x * (1-2*(i%2))),
                                  vectorAdd( vectorTimes(a2, a.halfSize.y * (i>=2 ? -1 : 1)),
                                             vectorTimes(a3, 0)));
                    break;
            }
            switch(lastSeparartingAxis)
            {
                case 6: case 9: case 12:
                    halfEdgeB = vectorTimes(b1, b.halfSize.x);
                    halfOffsetB[i] = vectorAdd( vectorTimes(b1, 0),
                                  vectorAdd( vectorTimes(b2, b.halfSize.y * (1-2*(i%2))),
                                             vectorTimes(b3, b.halfSize.z * (i>=2 ? -1 : 1))));
                    break;
                case 7: case 10: case 13:
                    halfEdgeB = vectorTimes(b2, b.halfSize.y);
                    halfOffsetB[i] = vectorAdd( vectorTimes(b1, b.halfSize.x * (1-2*(i%2))),
                                  vectorAdd( vectorTimes(b2, 0),
                                             vectorTimes(b3, b.halfSize.z * (i>=2 ? -1 : 1))));
                    break;
                case 8: case 11: case 14:
                    halfEdgeB = vectorTimes(b3, b.halfSize.z);
                    halfOffsetB[i] = vectorAdd( vectorTimes(b1, b.halfSize.x * (1-2*(i%2))),
                                  vectorAdd( vectorTimes(b2, b.halfSize.y * (i>=2 ? -1 : 1)),
                                             vectorTimes(b3, 0)));
                    break;
            }
        }
        *normal = vectorNormalize( vectorCross(halfEdgeA, halfEdgeB) );

        int edgeAi, edgeBi;
        int edgeA, edgeB;
        minDistance = -1;
        for(edgeAi = 0; edgeAi<4; edgeAi++)
            for(edgeBi = 0; edgeBi<4; edgeBi++)
            {
                distance = vectorDot(*normal, vectorAdd(a.position, halfOffsetA[edgeAi])) - vectorDot(*normal, vectorAdd(b.position, halfOffsetB[edgeBi]));
                distance = fabs(distance);
                if(minDistance == -1 || distance < minDistance)
                {
                    minDistance = distance;
                    edgeA = edgeAi;
                    edgeB = edgeBi;
                }

            }

        struct Vector pointEdgeA = vectorAdd(a.position, halfOffsetA[edgeA]);
        struct Vector pointEdgeB = vectorAdd(b.position, halfOffsetB[edgeB]);

        struct Vector rayVector = vectorNormalize(halfEdgeA);
        struct Vector rayPoint = pointEdgeA;
        struct Vector planePoint = pointEdgeB;
        struct Vector planeNormal = vectorNormalize(vectorCross(vectorNormalize(halfEdgeB), *normal));
        // ray - plane intersection
        double cosAlpha = vectorDot(rayVector, planeNormal);
        double distance = vectorPointPlaneDistance(rayPoint, planePoint, planeNormal);
        struct Vector pointA = vectorAdd(rayPoint, vectorTimes(rayVector, cosAlpha*distance)) ;

        rayVector = vectorNormalize(halfEdgeB);
        rayPoint = pointEdgeB;
        planePoint = pointEdgeA;
        planeNormal = vectorNormalize(vectorCross(vectorNormalize(halfEdgeA), *normal));
        // ray - plane intersection
        cosAlpha = vectorDot(rayVector, planeNormal);
        distance = vectorPointPlaneDistance(rayPoint, planePoint, planeNormal);
        struct Vector pointB = vectorAdd(rayPoint, vectorTimes(rayVector, cosAlpha*distance)) ;
        *point = vectorTimes(vectorAdd(pointA, pointB),0.5);
    }

    /* normal should point in direction from A to B*/

    double smallValue = 0.001;
    if(vectorLength(vectorSub(vectorAdd(*point,vectorTimes(*normal, smallValue)), a.position))
            <
       vectorLength(vectorSub(vectorAdd(*point,vectorZero()), a.position))) /*  |point + normal - A| < |point-A| */
            *normal = vectorTimes(*normal, -1.0);
    *normal = vectorNormalize(*normal);

}
