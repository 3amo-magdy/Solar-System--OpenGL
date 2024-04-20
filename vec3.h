//
// Created by Amr Magdy on 5/10/2023.
//

#ifndef VEC_H
#define VEC_H


class vec3 {
public:
    float x{};
    float y{};
    float z{};
    vec3();
    vec3(float  x,float y,float z);
};

vec3* addVectors(vec3 v1, vec3 v2);

vec3* subVectors(vec3 v1, vec3 v2);

vec3* scaleVectors(vec3 v, float s);

vec3* normalizeVector(vec3 v);

vec3* crossVectors(vec3 u, vec3 v);

float magnitude(vec3 v);

float dotVectors(vec3 v1, vec3 v2);

float angle(vec3 v1, vec3 v2);

#endif //VEC_H
