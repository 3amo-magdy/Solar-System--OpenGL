#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"

struct cam
{
    vec3* position;        // Camera position
    vec3* n;   // Camera view direction
    vec3* v;        // Up vector
    vec3* u;     // Right vector
};

extern cam camera;

void initCamera(vec3* position, vec3* direction, vec3* upVector, vec3* rightVector);

void cameraMoveForward(float speed);    // Move the camera forward
void cameraMoveBackward(float speed);   // Move the camera backward
void cameraMoveRight(float speed);      // Move the camera to the right
void cameraMoveLeft(float speed);       // Move the camera to the left
void cameraMoveUp(float speed);         // Move the camera up
void cameraMoveDown(float speed);       // Move the camera down

void cameraMove(vec3* direction);       // Move the camera in a specific direction

void cameraRotateX(float angle);        // Rotate the camera around the x-axis
void cameraRotateY(float angle);        // Rotate the camera around the y-axis
void cameraRotateZ(float angle);        // Rotate the camera around the z-axis

#endif //CAMERA_H
