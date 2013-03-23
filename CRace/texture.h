#ifndef TEXTURE_H
#define TEXTURE_H

#include "common.h"

struct TextureManager
{
    GLuint texture_id;
    char* filename;
    struct TextureManager* left;
    struct TextureManager* right;
};

long loadBmpTex(char * filename, BOOL mipmap);
struct TextureManager* newTextureManager();
void delTextureManager(struct TextureManager* textureMan);
long getTexture(struct TextureManager* textureMan, char* name, BOOL mipmap);
#endif /*TEXTURE_H*/


