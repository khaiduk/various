#ifndef TERRAIN_H
#define TERRAIN_H

#include "common.h"
#include "vector.h"
#include "texture.h"

#define TILE_SIZE 5

struct Terrain
{
    int width, height;
    char **texmap;
    float **heightmap;
    long groundTexture;
    long roadTexture;
};

struct Terrain newTerrain(struct TextureManager* textureManager);
void delTerrain(struct Terrain terrain);
double terrainGetHeight(const struct Terrain* terrain, double x, double z);
void terrainRender(const struct Terrain* terrain);
#endif /*TERRAIN_H*/
