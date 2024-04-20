//
// Created by amr on 5/10/2023.
//

#include <cmath>
#include "vec3.h"

vec3 *addVectors(vec3 vector1, vec3 vector2)
{
    vec3* res = new vec3(vector1.x + vector2.x, vector1.y + vector2.y, vector1.z + vector2.z);

    return res;
};

vec3 *subVectors(vec3 vector1, vec3 vector2)
{
    vec3* res = new vec3();
    res->x = vector1.x - vector2.x;
    res->y = vector1.y - vector2.y;
    res->z = vector1.z - vector2.z;

    return res;
};

float dotVectors(vec3 vector1, vec3 vector2)
{
    return vector1.x * vector2.x + vector1.y * vector2.y +vector1.z * vector2.z;
};

float angle(vec3 v1, vec3 v2){
    return acos(dotVectors(v1,v2)/(magnitude(v1)* magnitude(v2))) * 180.0/M_PI;
}

vec3 * scaleVectors(vec3 vector, float size)
{
    vec3* res = new vec3();
    res->x = vector.x * size;
    res->y = vector.y * size;
    res->z = vector.z * size;
    return res;
};


float  magnitude(vec3 v)
{
    return (float)(sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z)));
};

vec3 * normalizeVector(vec3 v)
{
    float l = magnitude(v);
    if (l == 0.0f) return new vec3(0.0f,0.0f,0.0f);
    vec3* res  = new vec3();
    res->x = v.x / l;
    res->y = v.y / l;
    res->z = v.z / l;
    return res;
};

vec3 * crossVectors(vec3 u, vec3 v)
{
    vec3* resVector = new vec3();
    resVector->x = u.y * v.z - u.z * v.y;
    resVector->y = u.z * v.x - u.x * v.z;
    resVector->z = u.x * v.y - u.y * v.x;
    return resVector;
};

vec3::vec3() {

}

vec3::vec3(float x, float y, float z):x(x),y(y),z(z){};

