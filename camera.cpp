//
// Created by Amr Magdy on 5/10/2023.
//

#include "vec3.h"
#include <cmath>
#include <iostream>
#include "camera.h"

#define PI M_PI

cam camera;  // Define the single global cam instance.

// initialize the camera with initial position, direction, up vector, and right vector
void initCamera(vec3* position, vec3* direction, vec3* upVector, vec3* rightVector)
{
    camera.position = position; // camera position to world origin.
    camera.n = direction;       // camera's own Z
    camera.u = rightVector;     // camera's own X
    camera.v = upVector;        // camera's own Y

}

// Move the camera in a specific direction
void cameraMove(vec3* direction)
{
    camera.position = addVectors(*camera.position, *direction);
}

// Move the camera forward by a given tr_speed
void cameraMoveForward(float speed)
{
    camera.position = addVectors(*camera.position, *scaleVectors(*camera.n, speed));
}

// Move the camera backward by a given tr_speed
void cameraMoveBackward(float speed)
{
    camera.position = addVectors(*camera.position, *(scaleVectors(*camera.n, -speed)));
}

// Move the camera to the right by a given tr_speed
void cameraMoveRight(float speed)
{
    camera.position = addVectors(*camera.position, *scaleVectors(*camera.u, speed));
}

// Move the camera to the left by a given tr_speed
void cameraMoveLeft(float speed)
{
    camera.position = addVectors(*camera.position, *scaleVectors(*camera.u, -speed));
}

// Move the camera up by a given tr_speed
void cameraMoveUp(float speed)
{
    camera.position = addVectors(*camera.position, *(scaleVectors(*camera.v, speed)));
}

// Move the camera down by a given tr_speed
void cameraMoveDown(float speed)
{
    camera.position = addVectors(*camera.position, *scaleVectors(*camera.v, -speed));
}

// Rotate the camera around the x-axis by a given angle
void cameraRotateX(float angle)
{
    // Rotate view direction around the right vector:
    camera.n = normalizeVector(*(addVectors(*(scaleVectors(*camera.n, std::cos(angle * (PI / 180)))),
                                            *(scaleVectors(*camera.v, std::sin(angle * (PI / 180)))))));

    // Compute the new up vector (by cross product)
    camera.v = scaleVectors(*crossVectors(*camera.n, *camera.u), -1);
}

// Rotate the camera around the y-axis by a given angle
void cameraRotateY(float angle)
{
    // Rotate view direction around the up vector:
    camera.n = normalizeVector(*(subVectors(*(scaleVectors(*camera.n, std::cos(angle * (PI / 180)))),
                                            *(scaleVectors(*camera.u, std::sin(angle * (PI / 180)))))));

    // Compute the new right vector (by cross product)
    camera.u = crossVectors(*camera.n, *camera.v);
}

// Rotate the camera around the z-axis by a given angle
void cameraRotateZ(float angle)
{
    // Rotate view direction around the right vector:
    camera.u = normalizeVector(*(addVectors(*(scaleVectors(*camera.u, cos(angle * (PI / 180)))),
                                            *(scaleVectors(*camera.v, sin(angle * (PI / 180)))))));

    // Compute the new up vector (by cross product)
    camera.v = scaleVectors(*crossVectors(*camera.n, *camera.u), -1);
}

