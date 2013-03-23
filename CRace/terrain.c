#include "terrain.h"

struct Terrain newTerrain(struct TextureManager* textureManager)
{
    int i;
    struct Terrain terrain;
    terrain.width = 40;
    terrain.height = 40;
    terrain.groundTexture = getTexture(textureManager, "grass.bmp", TRUE);
    terrain.roadTexture = getTexture(textureManager, "road.bmp", TRUE);

    terrain.texmap=malloc(terrain.height * sizeof(*terrain.texmap));
    if(!terrain.texmap)
    {
         printf("newTerrain: cannot alocate memory");
         return terrain;
    }
    for(i=0;i<terrain.height;i++)
        if(! (terrain.texmap[i]=malloc(terrain.width * sizeof(**terrain.texmap))))
        {
            printf("newTerrain: cannot alocate memory");
            terrain.height = i;
            break;
        }


    terrain.heightmap=malloc(terrain.height * sizeof(*terrain.heightmap));
    if(!terrain.heightmap)
    {
         printf("newTerrain: cannot alocate memory");
         return terrain;
    }
    for(i=0;i<terrain.height;i++)
        if(! (terrain.heightmap[i]=malloc(terrain.width * sizeof(**terrain.heightmap))))
        {
            printf("newTerrain: cannot alocate memory");
            terrain.height = i;
            break;
        }

    for(i=0;i<terrain.width*terrain.height;i++)
    {
        terrain.texmap[i/terrain.height][i%terrain.width]='*';
        terrain.heightmap[i/terrain.height][i%terrain.width]=0.0;
    }
    return terrain;
}

void delTerrain(struct Terrain terrain)
{
    int i;
    for(i = 0; i < terrain.height; i++)
    {
        free(terrain.texmap[i]);
        free(terrain.heightmap[i]);
    }
	free(terrain.texmap);
	free(terrain.heightmap);
}

double terrainGetHeight(const struct Terrain* terrain, double x, double z)
{
    int i,j;
    float p00, p01, p10, p11;
    float dx, dz;

    float tmp = x;
    x = z;
    z = tmp;

    i = x/TILE_SIZE + terrain->width/2;
    j = z/TILE_SIZE + terrain->height/2;
    if(i<0) i=0;
    if(j<0) j=0;
    if(i>=terrain->width-1) i=terrain->width-2;
    if(j>=terrain->height-1) j=terrain->height-2;
    p00 = terrain->heightmap[i][j];
    p01 = terrain->heightmap[i][j+1];
    p10 = terrain->heightmap[i+1][j];
    p11 = terrain->heightmap[i+1][j+1];
    dx = x/TILE_SIZE - floor(x/TILE_SIZE);
    dz = z/TILE_SIZE - floor(z/TILE_SIZE);
    return p00*(1-dx)*(1-dz)+p10*dx*(1-dz) + p01*(1-dx)*dz + p11*dx*dz;
    return sin(sqrt(x*x/10 + z*z/3)/3)+1;
}

void terrainRender(const struct Terrain* terrain)
{
    int i, j;
    double u, v, du, dv;
    double x,z;

    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glColor4f(0.5,0.5,0.5,0.0);
    glEnable(GL_TEXTURE_2D);
    for(i=0;i<40;i++)
        for(j=0;j<40;j++)
        {
            x= (i - terrain->width/2)*TILE_SIZE;
            z= (j - terrain->height/2)*TILE_SIZE;
            switch(terrain->texmap[j][i])
            {
                case '*':
                    glBindTexture(GL_TEXTURE_2D, terrain->groundTexture);
                    u=0;
                    v=0;
                    du=1;
                    dv=1;
                    break;
                case '-':
                    glBindTexture(GL_TEXTURE_2D, terrain->roadTexture);
                    u=0;
                    v=0.5;
                    du=0.5;
                    dv=0.5;
                    break;
                case '|':
                    glBindTexture(GL_TEXTURE_2D, terrain->roadTexture);
                    u=0.5;
                    v=0;
                    du=0.5;
                    dv=0.5;
                    break;
                case '#': default:
                    glBindTexture(GL_TEXTURE_2D, terrain->roadTexture);
                    u=0;
                    v=0;
                    du=0.5;
                    dv=0.5;

            }
            glBegin(GL_QUADS);
            glNormal3f(0,1,0);
            glTexCoord2f(u,v);
            glVertex3f(x, terrainGetHeight(terrain,x,z), z);
            glTexCoord2f(u,v+dv);
            glVertex3f(x, terrainGetHeight(terrain,x,z+TILE_SIZE), z+TILE_SIZE);
            glTexCoord2f(u+du,v+dv);
            glVertex3f(x+TILE_SIZE, terrainGetHeight(terrain,x+TILE_SIZE,z+TILE_SIZE), z+TILE_SIZE);
            glTexCoord2f(u+du,v);
            glVertex3f(x+TILE_SIZE, terrainGetHeight(terrain,x+TILE_SIZE,z), z);
            glEnd();
        }
}
