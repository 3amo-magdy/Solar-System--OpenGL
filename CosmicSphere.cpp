//
// Created by Amr Magdy on 5/8/2023.
//
#include "CosmicSphere.h"
#include <algorithm>
static void LoadTextureFromImg(const char* location, GLuint *texture){
    FIBITMAP* bitmap = FreeImage_Load(
            FreeImage_GetFileType(location, 0),
            location);
    FIBITMAP *pImage = FreeImage_ConvertTo32Bits(bitmap);
    unsigned int nWidth = FreeImage_GetWidth(pImage);
    unsigned int nHeight = FreeImage_GetHeight(pImage);

    glBindTexture(GL_TEXTURE_2D, *texture); // Bind that texture temporarily
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, nWidth, nHeight,
                 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (void*)FreeImage_GetBits(pImage));
    FreeImage_Unload(pImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    std::cout << "Texture \"" << location << "\" successfully loaded.\n";
}

CosmicSphere::CosmicSphere(float radius, float distance_from_sun, float speed, float sr_speed, char* texture_path):
        radius(radius), distance_from_rotation_target(distance_from_sun), tr_speed(speed), sr_speed(sr_speed)
{
    glGenTextures(1, &this->texture);             // Generate a texture
    LoadTextureFromImg(texture_path, &this->texture);
    geometric_data = gluNewQuadric();
}

void CosmicSphere::draw() {
    glPushMatrix();

    GLfloat materialAmbient[] = { 0, 0.0, 0.0, 1 };
    GLfloat materialDiffuse[] = { 1, 1, 1, 1 };
    GLfloat materialSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    GLfloat materialEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat materialShininess = 100.0f;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    gluQuadricDrawStyle(geometric_data, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    gluQuadricTexture(geometric_data, GL_TRUE);
    gluQuadricNormals(geometric_data, GLU_SMOOTH);
    gluSphere(geometric_data, radius, 80, 100);

    glPopMatrix();
}

Star::Star(float radius, float sr_speed, char *texture_path , GLenum light, float r, float g, float b)
:light(light), CosmicSphere(radius, 0, 0, sr_speed,texture_path)
{
    float lightAmb[] = {1,1,1,1};
    static float spec[] = {1,1,1,1};
    static float diff[] = {r,g,b,1};

    glLightfv(light, GL_AMBIENT,lightAmb);
    glLightfv(light, GL_DIFFUSE, diff);
    glLightfv(light, GL_SPECULAR, spec);

}

void Star::draw() {
//    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(1,1,1);

// Set material properties
    GLfloat materialAmbient[] = { 1, 1, 1, 1 };
    GLfloat materialDiffuse[] = { 1, 1, 1, 1.0 };
    GLfloat materialSpecular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialEmission[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    GLfloat materialShininess = 2000.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);

    float lightPos[] = {0, 0, 0, 1 };
    glLightfv(light, GL_POSITION, lightPos);

    glColor3f(1.0f, 1.0f, 1.0f);
    gluQuadricDrawStyle(geometric_data, GLU_FILL);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    gluQuadricTexture(geometric_data, GL_TRUE);
    gluQuadricNormals(geometric_data, GLU_SMOOTH);
    gluSphere(geometric_data, radius, 200, 200);
    glDisable(GL_BLEND_COLOR);
    glEnable(GL_DEPTH_TEST);

    glPopMatrix();
}


void drawTexturedDisk(float innerRadius, float outerRadius, int numSegments)
{
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= numSegments; i++)
    {
        float theta = 2.0f * M_PI * i / numSegments;

        // Calculate the vertex positions
        float xInner = innerRadius * cos(theta);
        float yInner = innerRadius * sin(theta);
        float xOuter = outerRadius * cos(theta);
        float yOuter = outerRadius * sin(theta);

        // Calculate the texture coordinates
        float s =  static_cast<float>(i) / static_cast<float>(numSegments);

        // Inner vertex
        glTexCoord2f(0.1f, s);
        glVertex2f(xInner, yInner);

        // Outer vertex
        glTexCoord2f(0.9f, s);
        glVertex2f(xOuter, yOuter);
    }

    glEnd();
}

Ring::Ring(float inner, float outer, float tr_speed, char *texture_path)
:inner_radius(inner), CosmicSphere(outer, 0, tr_speed, 0, texture_path){};

void Ring::draw() {
    glPushMatrix();
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    GLfloat materialAmbient[] = { 0.0, 0.0, 0.0, 1 };
    GLfloat materialDiffuse[] = { 1, 1, 1, 1 };
    GLfloat materialSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat materialEmission[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    GLfloat materialShininess = 100.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, materialEmission);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShininess);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    gluQuadricDrawStyle(geometric_data, GLU_FILL);
    glTranslatef(0,0,0.04);
    drawTexturedDisk(inner_radius, radius, 100);
    glTranslatef(0,0,-0.04);
    drawTexturedDisk(inner_radius, radius, 100);
    glTranslatef(0,0,-0.04);
    drawTexturedDisk(inner_radius, radius, 100);


    glPopMatrix();

}
