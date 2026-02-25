#ifndef MINECRAFT_CORE_MATH3D_H
#define MINECRAFT_CORE_MATH3D_H

#include <math.h>
#include <cglm/cglm.h>

#define vec2i(v, x, y) v[0] = (int)(x); v[1] = (int)(y)
#define vec3i(v, x, y, z) v[0] = (int)(x); v[1] = (int)(y); v[2] = (int)(z)
#define vec4i(v, x, y, z, w) v[0] = (int)(x); v[1] = (int)(y); v[2] = (int)(z); v[3] = (int)(w)

#define vec2f(v, x, y) v[0] = (float)(x); v[1] = (float)(y)
#define vec3f(v, x, y, z) v[0] = (float)(x); v[1] = (float)(y); v[2] = (float)(z)
#define vec4f(v, x, y, z, w) v[0] = (float)(x); v[1] = (float)(y); v[2] = (float)(z); v[3] = (float)(w)


typedef struct Transform2D
{   
    mat3 matrix;
    vec2 position;
    vec2 scale;
    vec2 rotation; 
}Transform2D;

typedef struct Transform3D
{
    mat4 matrix;
    vec3 position;
    vec3 scale;
    vec3 rotation; 
}Transform3D;

typedef struct EulerOrientation
{   
    double pitch;
    double yaw;
    double roll;
}EulerOrientation;

#endif