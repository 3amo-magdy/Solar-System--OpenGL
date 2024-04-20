//
// Created by Amr Magdy on 5/8/2023.
//

#ifndef COSMICSPHERE_H
#define COSMICSPHERE_H

#include <iostream>

#include "libraries/include/GL/glew.h"
#include "libraries/include/GL/freeglut.h"
#include "FreeImage.h"

#include <cmath>
using namespace std;

class CosmicSphere {
protected:
    // the geometrical object that would hold the points of the shape.
    GLUquadric* geometric_data;
    // glu texture index
    GLuint texture;
    float radius;
public:
    float distance_from_rotation_target;
    float tr_speed;  // around another-CosmicSphere rotation tr_speed
    float sr_speed; // self-rotation sr_speed
    CosmicSphere(float radius, float distance_from_target, float tr_speed, float sr_speed, char* texture_path);
    virtual void draw();
};

class Star: public CosmicSphere {
private:
    GLenum light;   // glu light index
public:
    Star(float radius, float sr_speed, char* texture_path, GLenum light, float r, float g, float b);
    void draw() override;
};

class Ring: public CosmicSphere{
private:
    float inner_radius;
public:
    Ring(float inner, float outer, float tr_speed, char* texture_path);
    void draw() override;

};
static void draw_rings(float inner, float outer){

}



static void draw_orbit(float r){
    glDisable(GL_LIGHTING);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glLineWidth(1);
    glColor4ub(255, 255, 255, 60);
    glBegin(GL_LINE_LOOP);
    for(int i = 0; i < 720; i++)
    {
        float theta = (2.0f * M_PI * float(i)/720);
        float x = r * cosf(theta);
        float y = r * sinf(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
}
#endif //COSMICSPHERE_H
