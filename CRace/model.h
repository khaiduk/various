#ifndef MODEL_H
#define MODEL_H

#include "vector.h"
#include "texture.h"
#include "common.h"

struct modelTriangle
{
    long textureName;
    struct Vector vertices[3];
    struct Vector texture[3]; /* x -> u, y -> v, z (ignored)*/
    struct Vector normal[3];
};

struct modelTriangleArray
{
    struct modelTriangle* array;
    int size;
    int lastElement;/*index of element to be add*/
};

struct Model
{
    GLuint texture;
    struct modelTriangleArray triangles;
    char filename[256];
};

void delmodelTriangleArray(struct modelTriangleArray array);
struct modelTriangleArray newmodelTriangleArray(void);
void addTriangleToArray(struct modelTriangleArray *array, struct modelTriangle triangle);
struct Model* modelLoadFromFile(char* filename, struct TextureManager* textureManager);
void delmodel(struct Model* model);
void modelDisplay(const struct Model* model);
#endif /*MODEL_H*/

