// Solar System demo in OpenGL.
// Author: Amr Magdy.

// controls:
// WASD to move
// arrows to rotate.
// Hit left-shift repeatedly to use boost (accelerate).
// O to trigger orbits.
// P to stop the time.
// F or F11 to trigger fullscreen.



#include "CosmicSphere.h"
#include "vec3.h"
#include "camera.h"

using namespace std;

#define speed_up 0.2            // animation speed up.
#define spaceship_radius 120
#define planets_count 8
#define small_view_ratio 0.2    // Bottom-Right view ratio to Main view.


CosmicSphere* sun;
CosmicSphere* planets[planets_count];
CosmicSphere* moon;
CosmicSphere* saturn_ring;

float planet_angle_sun[planets_count] = {0};
float planet_angle_self[planets_count] = {0};
GLfloat moon_angle_earth = 0;
GLfloat moon_angle_self = 0;

GLfloat ring_angle = 0;

GLfloat sun_angle_self = 0;

static bool orbits = true; // orbits visible or not.
static bool isAnimate = true; // animating or paused.
static int last_update; // timestamp of last drawing routine call.
static int width, height; // Size of the OpenGL window.

static unsigned int spacecraft; // Display lists base index.
static float spaceship_speed = 5;     // spaceship movement tr_speed

struct keypress
{
    bool W = false;
    bool S = false;
    bool A = false;
    bool D = false;
    bool Z = false;
    bool X = false;
    bool Q = false;
    bool E = false;
    bool UP = false;
    bool DOWN = false;
    bool LEFT = false;
    bool RIGHT = false;
    bool SHIFT = false;
};
keypress keysPressed;


void draw_planets() {
    // draw planets.
    int i = 0;
    for (CosmicSphere* planet:planets) {
        glPushMatrix();
        // draw the orbit if enabled
        if(orbits) {
//            glLineWidth(1);
            draw_orbit(planet->distance_from_rotation_target);
        }
        // rotate around sun
        glRotatef(planet_angle_sun[i],0,0,1);
        glTranslatef(0, planet->distance_from_rotation_target, 0);
        // draw moon if the planet was earth
        if(i == 2){
            glPushMatrix();
            glRotatef(22,1,0,0);
            if(orbits) {
                draw_orbit(moon->distance_from_rotation_target);
            }
            // rotate around earth
            glRotatef(moon_angle_earth,0,0,1);
            glTranslatef(0, moon->distance_from_rotation_target, 0);
            // rotate around self axis
            glRotatef(moon_angle_self,1,1,1);
            moon -> draw();
            glPopMatrix();
        }
        // draw saturn_ring
        if(i == 5){
            glPushMatrix();
            glRotatef(-10, 1, 0, 0);
            glRotatef(ring_angle, 0, 0, 1);
            saturn_ring->draw();
            glPopMatrix();
        }
        // rotate around self axis
        glRotatef(planet_angle_self[i],1,1,1);
        planet->draw();
        glPopMatrix();
        i++;
    }
}
void draw_spaceship(){
    glPushMatrix();
    glTranslatef(camera.position->x, camera.position->y, camera.position->z);
    glCallList(spacecraft);
    glPopMatrix();
}

void draw(void)
{
    float globAmb[] = { 0, 0, 0, 1.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1); // Enable local viewpoint

    glEnable(GL_LIGHT0);
    // main view:
    glLoadIdentity();

    glEnable(GL_SCISSOR_TEST);
    glScissor(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    glViewport(0, 0, width, height);

    vec3* viewPoint = (addVectors(*camera.position, *camera.n));

    gluLookAt(camera.position->x, camera.position->y, camera.position->z,   // eye
              viewPoint->x, viewPoint->y, viewPoint->z,                // ref point
              camera.v->x, camera.v->y, camera.v->z);                         // up

    // draw spaceship
    cameraMoveDown(spaceship_radius + spaceship_radius * 0.25);
    draw_spaceship();
    cameraMoveUp(spaceship_radius + spaceship_radius * 0.25);


    // draw sun.
    glPushMatrix();
    glRotatef(sun_angle_self,1,-1,1);     // sun rotation around its axis.
    sun->draw();
    glPopMatrix();

    //draw planets
    draw_planets();


    /*
     * SMALL BOTTOM-RIGHT VIEW
     */
    glEnable(GL_SCISSOR_TEST);
    glScissor((1.0 - small_view_ratio) * (float)width, 0 ,
              small_view_ratio * (float)width, small_view_ratio * (float)height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);
    glViewport((1.0 - small_view_ratio) * (float)width, 0 ,
               small_view_ratio * (float)width, small_view_ratio * (float)height);

    glLoadIdentity();

    // look at the sun from above.
    gluLookAt(0, 0, 3800,
              0, 0,0,
              0.0,
              1.0,
              0.0);

    // draw spacecraft
    glDisable(GL_LIGHTING);
    draw_spaceship();
    glEnable(GL_LIGHTING);


    // draw sun
    sun->draw();
    // draw planets
    draw_planets();

    glEnable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

//processing keyboard inputs
void handle_input();

// update functions.
void update()
{
    int now = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = now - last_update;
    if (elapsedTime > 20)
    {
        // rotate planets
        for (int i = 0; i < planets_count;i++) {
            planet_angle_self[i] += ((float)elapsedTime/1000)* (planets[i]->sr_speed) * speed_up ;
            planet_angle_sun[i] += ((float)elapsedTime/1000) * (planets[i]->tr_speed) * speed_up ;
            if(planet_angle_self[i]>360){
                planet_angle_self[i] -= 360;
            }
            if(planet_angle_sun[i]>360){
                planet_angle_sun[i] -= 360;
            }
        }
        // rotate sun
        sun_angle_self +=  ((float)elapsedTime/1000)* sun->sr_speed * speed_up;
        if(sun_angle_self > 360){
            sun_angle_self -=360;
        }
        // rotate moon
        moon_angle_earth += ((float)elapsedTime/1000) * (moon->tr_speed) * speed_up ;
        moon_angle_self += ((float)elapsedTime/1000)* (moon->sr_speed) * speed_up ;
        if(moon_angle_earth>360){
            moon_angle_earth -= 360;
        }
        if(moon_angle_self>360){
            moon_angle_self -= 360;
        }
        // rotate saturn's ring
        ring_angle +=  ((float)elapsedTime/1000) * (saturn_ring->tr_speed) * speed_up;
        if(ring_angle > 360){
            ring_angle-=360;
        }
        // handle input
        handle_input();
        glutPostRedisplay();
        last_update = now;
    }
}
void paused_update(){
    int now = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = now - last_update;
    if (elapsedTime > 20)
    {
        handle_input();
        glutPostRedisplay();
        last_update = now;
    }
}
void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.0*w/h, 0.1, 9000.0);

    glMatrixMode(GL_MODELVIEW);
    // Pass the size of the OpenGL window.
    width = w;
    height = h;
}

void init(void)
{
    // initialize camera
    vec3 position = *(new vec3()); position.x = 0.0; position.y = 0.0; position.z = 4000.0;
    vec3 viewDirection = *new vec3(); viewDirection.x =0.0; viewDirection.y = 0.0; viewDirection.z = -1.0;
    vec3 upVector = *new vec3(); upVector.x = upVector.z = 0.0; upVector.y = 1.0;
    vec3 rightVector = *new vec3();  rightVector.z = rightVector.y = 0.0; rightVector.x = 1.0;
    initCamera(&position, &viewDirection, &upVector, &rightVector);
    cameraMoveBackward(3700);camera.position->z = 3700;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);

    spacecraft = glGenLists(1);
    glNewList(spacecraft, GL_COMPILE);
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glutSolidSphere(spaceship_radius, 100,100);
    glPopMatrix();
    glEndList();

    static  float s = 2;
    static  float a = 3;

    static float sun_rad = 10 * 139.268/s;

    // create the solar system objects
    sun = new Star(sun_rad,8,R"(textures\sun.jpg)",GL_LIGHT0,1,0.9,0.9);
    planets[0] = new CosmicSphere(24.39/s, sun_rad+58 * 2*a, 28.6, 70.1, R"(textures\mercury.jpg)");
    planets[1] = new CosmicSphere(60.52/s, sun_rad+108 * 2*a, 43, 120.65, R"(textures\venus.jpg)");
    planets[2] = new CosmicSphere(63.71/s, sun_rad+150 * 2*a, 24, 80, R"(textures\earth.jpg)");
    planets[3] = new CosmicSphere(33.90/s, sun_rad+200 * 1.8*a, 24.6, 109.53, R"(textures\mars.jpg)");
    planets[4] = new CosmicSphere(90.911/s, sun_rad+520 * 1.6*a, 9.9, 82.8, R"(textures\jupiter.jpg)");
    planets[5] = new CosmicSphere(58.232/s, sun_rad+730 * 1.4*a, 10.7, 72.3, R"(textures\saturn.jpg)");
    planets[6] = new CosmicSphere(50.362/s, sun_rad+990 * 1.2*a, 17.2, 62.1, R"(textures\uranus.jpg)");
    planets[7] = new CosmicSphere(48.622/s, sun_rad+1120* 1.0*a, 16.8, 51.2, R"(textures\neptune.jpg)");

    moon = new CosmicSphere(3,63.71/2 + 15, 25.145, 42,R"(textures\moon.jpg)");
    saturn_ring = new Ring((58.232+80)/s, (58.232+220)/s,50, R"(textures\ring.png)");

//    //initiate planets' angles at random:
//    for (int i = 0; i < planets_count; ++i) {
//        planet_angle_sun[i] = (rand()*359.0/RAND_MAX);
//    }

    // bind the updating function.
    last_update = glutGet(GLUT_ELAPSED_TIME);
    glutIdleFunc(update);

}



void reset();

void keyUp(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w': case 'W':
            keysPressed.W = false;
            break;
        case 's': case 'S':
            keysPressed.S = false;
            break;
        case 'a': case 'A':
            keysPressed.A = false;
            break;
        case 'd': case 'D':
            keysPressed.D = false;
            break;
        case 'z': case 'Z':
            keysPressed.Z = false;
            break;
        case 'x': case 'X':
            keysPressed.X = false;
            break;
        case 'q': case 'Q':
            keysPressed.Q = false;
            break;
        case 'e': case 'E':
            keysPressed.E = false;
            break;
        case 'r': case 'R':
            reset();
            break;
    }
}
void keyInput(unsigned char key, int x, int y)
{
    switch (key) {
        case 'w': case 'W':
            keysPressed.W = true;
            break;
        case 's': case 'S':
            keysPressed.S = true;
            break;
        case 'a': case 'A':
            keysPressed.A = true;
            break;
        case 'd': case 'D':
            keysPressed.D = true;
            break;
        case 'z': case 'Z':
            keysPressed.Z = true;
            break;
        case 'x': case 'X':
            keysPressed.X = true;
            break;
        case 'q': case 'Q':
            keysPressed.Q = true;
            break;
        case 'e': case 'E':
            keysPressed.E = true;
            break;
        case 'p':
        case 'P':
            if(isAnimate){
                glutIdleFunc(paused_update);
                glutPostRedisplay();
                isAnimate = false;
            }
            else{
                last_update = glutGet(GLUT_ELAPSED_TIME);
                glutIdleFunc(update);
                glutPostRedisplay();
                isAnimate = true;
            }
            break;
        case 'o':
        case 'O':
            orbits = !orbits;
            glutPostRedisplay();
            cout<< camera.position->x << " "<< camera.position->y<< " " << camera.position->z << "\n";
            break;
        case 'F':
        case 'f':
            glutFullScreenToggle();
            break;
    }

};
void keyUpSpecial(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP: keysPressed.UP = false; break;
        case GLUT_KEY_DOWN: keysPressed.DOWN = false; break;
        case GLUT_KEY_LEFT: keysPressed.LEFT = false; break;
        case GLUT_KEY_RIGHT: keysPressed.RIGHT = false; break;
        case GLUT_KEY_SHIFT_L: keysPressed.SHIFT = false; break;
        case GLUT_KEY_F11: glutFullScreenToggle();break;
    }
};
void keyboardSpecialKeyInput(int key, int x, int y)
{
    switch (key) {
        case GLUT_KEY_UP: keysPressed.UP = true; break;
        case GLUT_KEY_DOWN: keysPressed.DOWN = true; break;
        case GLUT_KEY_LEFT: keysPressed.LEFT = true; break;
        case GLUT_KEY_RIGHT: keysPressed.RIGHT = true; break;
        case GLUT_KEY_SHIFT_L: keysPressed.SHIFT = true; break;
    }
};
void handle_input() {
    if(keysPressed.SHIFT){
        if(spaceship_speed<30) {
            spaceship_speed += 0.3;
        }
    }
    else{
        if(spaceship_speed > 5) {
            spaceship_speed = 0.99 * spaceship_speed;
        }
    }
    if (keysPressed.W)
    {
        cameraMoveForward(spaceship_speed);
    };
    if (keysPressed.S)
    {
        cameraMoveBackward(spaceship_speed);
    };
    if (keysPressed.A)
    {
        cameraMoveLeft(spaceship_speed);
    };
    if (keysPressed.D)
    {
        cameraMoveRight(spaceship_speed);
    };
    if (keysPressed.Z)
    {
        cameraRotateZ(1.0 * log(spaceship_speed));
    };
    if (keysPressed.X)
    {
        cameraRotateZ(-1.0 * log(spaceship_speed));
    };
    if (keysPressed.UP)
    {
        cameraRotateX(1.0 * log(spaceship_speed));
    };
    if (keysPressed.DOWN)
    {
        cameraRotateX(-1.0* log(spaceship_speed));
    };
    if (keysPressed.LEFT)
    {
        cameraRotateY(1.0* log(spaceship_speed));
    };
    if (keysPressed.RIGHT)
    {
        cameraRotateY(-1.0* log(spaceship_speed));
    };
    if (keysPressed.Q) {
        cameraRotateZ(1.0* log(spaceship_speed));
    }
    if (keysPressed.E) {
        cameraRotateZ(-1.0* log(spaceship_speed));
    }

}

void reset() {
    camera.position->x = 0;
    camera.position->y = 0;
    camera.position->z = 0;
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitContextVersion(4, 3);
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
    glutInitWindowSize(960, 580);
    glutCreateWindow("solar system");
    glutDisplayFunc(draw);
    glutReshapeFunc(resize);
    glutSpecialFunc(keyboardSpecialKeyInput);
    glutSpecialUpFunc(keyUpSpecial);
    glutKeyboardFunc(keyInput);
    glutKeyboardUpFunc(keyUp);
//    glewExperimental = GL_TRUE;
    glutFullScreen();


    init();
    glutMainLoop();
}
