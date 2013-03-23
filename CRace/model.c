#include "model.h"

void delmodelTriangleArray(struct modelTriangleArray array)
{
    if(array.array)
        free(array.array);
    array.array=NULL;
}

struct modelTriangleArray newmodelTriangleArray(void)
{
    struct modelTriangleArray arr;
    arr.size=100;
    arr.lastElement=0;
    arr.array = malloc(arr.size * sizeof *(arr.array));
    if(!arr.array)
        printf("newmodelTriangleArray: cannot alocate memory");
    return arr;
}

void addTriangleToArray(struct modelTriangleArray *array, struct modelTriangle triangle)
{
    if(array->lastElement>=array->size)/*array is full*/
    {
        array->size = array->size+100;
        array->array = realloc(array->array, array->size * sizeof *array->array);
    }
    array->array[array->lastElement++]=triangle;
}

struct Model* modelLoadFromFile(char* filename, struct TextureManager* textureManager)
{
    long textureName=-1;
    char line[256];
    struct modelTriangleArray vertices;
    struct modelTriangleArray texture;
    //struct modelTriangleArray normal;
    struct Model* model;
    FILE* f;

    if(!(model = malloc(sizeof *model)))
    {
        printf("modelLoadFromFile: cannot alocate memory");
        return NULL;
    }
    model->triangles = newmodelTriangleArray();
    if(!(model->triangles.array))
    {
        printf("modelLoadFromFile: cannot alocate memory");
        free(model);
        return NULL;
    }
    vertices = newmodelTriangleArray();
    if(!(vertices.array))
    {
        printf("modelLoadFromFile: cannot alocate memory");
        delmodelTriangleArray(model->triangles);
        free(model);
        return NULL;

    }
    texture = newmodelTriangleArray();
    if(!(texture.array))
    {
        printf("modelLoadFromFile: cannot alocate memory");
        delmodelTriangleArray(vertices);
        delmodelTriangleArray(model->triangles);
        free(model);
        return NULL;

    }

    strncpy(model->filename, filename, 256);

    if(!(f = fopen(filename,"r")))
    {
        printf("modelLoadFromFile: cannot open file");
        delmodelTriangleArray(texture);
        delmodelTriangleArray(vertices);
        delmodelTriangleArray(model->triangles);
        free(model);
        return NULL;
    }

    while(!feof(f))
    {
        fgets(line, 256, f);
        if('u'==line[0])
        {
            if(line == strstr(line, "usemtl"))
            {
                char material[256];
                strcpy(material, line+7);//assuming material name is texture filename
#ifdef __linux__
                material[strlen(material)-2]='\0'; //replace newline character with '\0'
#else
                material[strlen(material)-1]='\0'; //replace newline character with '\0'
#endif
                textureName = getTexture(textureManager, material, TRUE);
            }
        }
        if('v'==line[0])
        {
            if(' '==line[1])
            {
                struct modelTriangle v;
                sscanf(line,"v %lf %lf %lf", &v.vertices[0].x, &v.vertices[0].y, &v.vertices[0].z);
                addTriangleToArray(&vertices, v);
            }
            if('t'==line[1])
            {
                struct modelTriangle v;
                sscanf(line,"vt %lf %lf", &v.vertices[0].x, &v.vertices[0].y);
                v.vertices[0].y = -v.vertices[0].y; //mirror y
                addTriangleToArray(&texture, v);
            }
        }
        else if('f'==line[0])
        {
            int i;
            int v[3];
            int t[3] = {0};
            int n[3];
            v[0]=-1;
            v[1]=-1;
            for(i=0;line[i];i++)
            {
                int j;
                char buffer[256];
                struct modelTriangle triangle;

                if(!isNum(line[i])) continue;

                j=0;
                while(isNum(line[i]))
                    buffer[j++]=line[i++];
                buffer[j]='\0';
                v[2]=atoi(buffer);  //verticle
                t[2]=-1;            //texture
                n[2]=-1;            //normal

                if('/'==line[i])
                {
                    i++;
                    if(isNum(line[i]))
                    {
                        j=0;
                        while(isNum(line[i]))
                            buffer[j++]=line[i++];
                        buffer[j]='\0';
                        t[2]=atoi(buffer);
                    }
                    if('/'==line[i])
                    {
                        i++;
                        if(isNum(line[i]))
                        {
                            j=0;
                            while(isNum(line[i]))
                                buffer[j++]=line[i++];
                            buffer[j]='\0';
                            n[2]=atoi(buffer);
                        }
                    }
                }

                if(-1==v[0])
                {
                    v[0]=v[2];
                    t[0]=t[2];
                    n[0]=n[2];
                    continue;
                }
                if(-1==v[1])
                {
                    v[1]=v[2];
                    t[1]=t[2];
                    n[1]=n[2];
                    continue;
                }

                triangle.vertices[0]=vertices.array[v[0]-1].vertices[0];
                triangle.vertices[1]=vertices.array[v[1]-1].vertices[0];
                triangle.vertices[2]=vertices.array[v[2]-1].vertices[0];

                triangle.texture[0]=texture.array[t[0]-1].vertices[0];
                triangle.texture[1]=texture.array[t[1]-1].vertices[0];
                triangle.texture[2]=texture.array[t[2]-1].vertices[0];

                // NORMALS --- TO DO
/*
                triangle.texture[0] = vectorZero();
                triangle.texture[0].y = 1.0;
                triangle.texture[1] = vectorZero();
                triangle.texture[2] = vectorZero();
                triangle.texture[2].x = 1.0;
                triangle.texture[2].y = 0.5;*/

                triangle.normal[0] = vectorNormalize(
                    vectorCross(
                        vectorSub(triangle.vertices[0],triangle.vertices[1]),
                        vectorSub(triangle.vertices[0],triangle.vertices[2])
                    )
                );
                triangle.normal[2] = triangle.normal[1] = triangle.normal[0];

                triangle.textureName = textureName;

                addTriangleToArray(&(model->triangles), triangle);
                v[1]=v[2];
                t[1]=t[2];
                n[1]=n[2];
            }
        }
    }

    fclose(f);
    delmodelTriangleArray(texture);
    delmodelTriangleArray(vertices);

    return model;
}

void delmodel(struct Model* model)
{
    if(model)
    {
        delmodelTriangleArray(model->triangles);
        free(model);
        model=NULL;
    }

}

void modelDisplay(const struct Model* model)
{
    if(!model)
    {
        printf("modelDisplay: no model");
        return;
    }
    int i,j;
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
    glColor4f(0.5,0.5,0.5,0.0);
    glEnable(GL_TEXTURE_2D);
    for(i=0;i<model->triangles.lastElement;i++)
    {
        glBindTexture(GL_TEXTURE_2D, model->triangles.array[i].textureName);
        glBegin(GL_TRIANGLES);
        for(j=0;j<3;j++)
        {
            glTexCoord2f(
                model->triangles.array[i].texture[j].x,
                model->triangles.array[i].texture[j].y);
            glNormal3f(
                model->triangles.array[i].normal[j].x,
                model->triangles.array[i].normal[j].y,
                model->triangles.array[i].normal[j].z);
            glVertex3f(
                model->triangles.array[i].vertices[j].x,
                model->triangles.array[i].vertices[j].y,
                model->triangles.array[i].vertices[j].z);
        }
        glEnd();
    }

}
