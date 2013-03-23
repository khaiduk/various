#ifndef COMMON_H
#define COMMON_H

#include <SDL/SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alut.h>

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define BOOL int
#define FALSE 0
#define TRUE 1

#define EPSILON 1.0e-10
#define PI 3.14159265

int isNum(char ch);

#endif /*COMMON_H*/
