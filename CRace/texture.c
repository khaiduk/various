#include "texture.h"

long loadBmpTex(char * filename, BOOL mipmap)
{
    GLuint textureName;
    GLenum textureFormat;
    static SDL_Surface* surface = NULL;
    if(!(surface = SDL_LoadBMP(filename)))
    {
        printf("loadBmpTex: cannot load bitmap: \"%s\"\n", filename);
        return -1;
    }

    if(4 == surface->format->BytesPerPixel) // with alpha
    {
        if(0x000000ff == surface->format->Rmask)
            textureFormat = GL_RGBA;
        else
            textureFormat = GL_BGRA;
    }
    else if(3 == surface->format->BytesPerPixel) // without alpha
    {
        if(0x000000ff == surface->format->Rmask)
            textureFormat = GL_RGB;
        else
            textureFormat = GL_BGR;
    }
    else //???
    {
        printf("loadBmpTex: cannot recognize bitmap format");
        return -1;
    }

    glGenTextures(1, &textureName);
    glBindTexture(GL_TEXTURE_2D, textureName);
    if(mipmap)
    {
        gluBuild2DMipmaps(GL_TEXTURE_2D, surface->format->BytesPerPixel, surface->w, surface->h,
                      textureFormat, GL_UNSIGNED_BYTE, surface->pixels);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, surface->format->BytesPerPixel, surface->w, surface->h, 0,
                      textureFormat, GL_UNSIGNED_BYTE, surface->pixels );
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    }

    SDL_FreeSurface(surface);

    return textureName;
}

struct TextureManager* newTextureManager()
{
    struct TextureManager* texman;
    if(!(texman = malloc(sizeof *texman)))
    {
        return NULL;
    }

    texman->texture_id = 0;
    texman->filename = NULL;
    texman->left = NULL;
    texman->right = NULL;

    return texman;
}

void delTextureManager(struct TextureManager* textureMan)
{
    if(!textureMan)
        return;
    free(textureMan->filename);
    delTextureManager(textureMan->left);
    delTextureManager(textureMan->right);
    free(textureMan);
}

long getTexture(struct TextureManager* textureMan, char* name, BOOL mipmap)
{
    if(!(textureMan->filename))
    {
        long texid = loadBmpTex(name, mipmap);
        if(-1 == texid)
            return -1;
        if(!(textureMan->filename = malloc(strlen(name)+1)))
            return -1;
        strcpy(textureMan->filename, name);
        textureMan->texture_id = texid;
        return textureMan->texture_id;
    }
    if(0 == strcmp(textureMan->filename, name))
    {
        return textureMan->texture_id;
    }
    if(strcmp(textureMan->filename, name) > 0)
    {
        if(!textureMan->left)
            if(!(textureMan->left = newTextureManager()))
                return -1;
        return getTexture(textureMan->left, name, mipmap);
    }
    else
    {
        if(!textureMan->right)
            if(!(textureMan->right = newTextureManager()))
                return -1;
        return getTexture(textureMan->right, name, mipmap);
    }
}
