#include <GL/glut.h>
#include <vector>
#include <string.h>
#include "opengl_conf.h"

using namespace std;

// global variable to define the length of the wall
int WALL_LENGTH = 15;

// fuction to clearing the buffer
void clear_buffer()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
}

// function for configuring lighting
void set_source_attributes()
{
    //glEnable(GL_NORMALIZE);

    // Enable lighting and set light source attributes
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // Light source attributes
    GLfloat LightAmbient[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat LightDiffuse[] = {0.3, 0.3, 0.3, 1.0};
    GLfloat LightSpecular[] = {0.4, 0.4, 0.4, 1.0};
    GLfloat LightPosition[] = {5.0, 5.0, 5.0, 1.0};

    // Configure OpenGL light source
    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, LightSpecular);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPosition);
}

// function for setting material properties
void set_material_properties()
{
    // Surface material attributes
    GLfloat material_Ka[] = {0.11, 0.06, 0.11, 1.0};
    GLfloat material_Kd[] = {0.43, 0.47, 0.54, 1.0};
    GLfloat material_Ks[] = {0.33, 0.33, 0.52, 1.0};
    GLfloat material_Ke[] = {0.1, 0.0, 0.1, 1.0};
    GLfloat material_Se = 10;

    // Set material properties
    glMaterialfv(GL_FRONT, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT, GL_SHININESS, material_Se);
}

// function for disablening the lightening
void disable_lightening()
{
    // Disable lighting
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHTING);
}

// function for reshaping the window
void reshape(int w, int h)
{

    // viewport
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);

    // projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 2000.0);
}

// function for setting the time
void timer(int value)
{
    // render
    glutPostRedisplay();

    // reset timer
    // 16 ms per frame ( about 60 frames per second )
    glutTimerFunc(60, timer, 0);
}

// initialization function to define the lookat positions and begin GL_Lines mode
void gl_init_wall(int eyeX, int eyeY, int eyeZ){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, 0, 0, 0, 0, 1, 0);
    glBegin(GL_LINES);
}

// helper function to call the corresponding functions all at once
void draw_walls(){
    
    gl_init_wall();

    draw_ground();
    draw_front_wall();
    draw_back_wall();
    draw_left_wall();
    draw_right_wall();

    glEnd();
}

// the function to draw the ground
void draw_ground(float dt_ver, float dt_hor){
    for (float x = -WALL_LENGTH; x <= WALL_LENGTH; x += dt_ver) {
        glVertex3f(x, 0, -WALL_LENGTH);
        glVertex3f(x, 0, WALL_LENGTH);
    }
    for (float z = -WALL_LENGTH; z <= WALL_LENGTH; z += dt_hor) {
        glVertex3f(-WALL_LENGTH, 0, z);
        glVertex3f(WALL_LENGTH, 0, z);
    }
}

// the function to draw the left wall
void draw_left_wall(float dt_ver, float dt_hor){
    for (float y = 0; y <= WALL_LENGTH; y += dt_ver) {
        glVertex3f(-WALL_LENGTH, y, -WALL_LENGTH);
        glVertex3f(-WALL_LENGTH, y, WALL_LENGTH);
    }
    for (float z = -WALL_LENGTH; z <= WALL_LENGTH; z += dt_hor) {
        glVertex3f(-WALL_LENGTH, 0, z);
        glVertex3f(-WALL_LENGTH, WALL_LENGTH, z);
    }
}

// the function to draw right wall
void draw_right_wall(float dt_ver, float dt_hor){
    for (float y = 0; y <= WALL_LENGTH; y += dt_ver) {
        glVertex3f(WALL_LENGTH, y, -WALL_LENGTH);
        glVertex3f(WALL_LENGTH, y, WALL_LENGTH);
    }
    for (float z = -WALL_LENGTH; z <= WALL_LENGTH; z += dt_hor) {
        glVertex3f(WALL_LENGTH, 0, z);
        glVertex3f(WALL_LENGTH, WALL_LENGTH, z);
    }
    return;
}

// the function to draw front wall
void draw_front_wall(float dt_ver, float dt_hor){
    for (float y = 0; y <= WALL_LENGTH; y += dt_ver) {
        glVertex3f(-WALL_LENGTH, y, -WALL_LENGTH);
        glVertex3f(WALL_LENGTH, y, -WALL_LENGTH);
    }
    for (float x = -WALL_LENGTH; x <= WALL_LENGTH; x += dt_hor) {
        glVertex3f(x, 0, -WALL_LENGTH);
        glVertex3f(x, WALL_LENGTH, -WALL_LENGTH);
    }
}

// the function to draw back wall
void draw_back_wall(float dt_ver, float dt_hor){
    for (float y = 0; y <= WALL_LENGTH; y += dt_ver) {
        glVertex3f(-WALL_LENGTH, y, WALL_LENGTH);
        glVertex3f(WALL_LENGTH, y, WALL_LENGTH);
    }
    for (float x = -WALL_LENGTH; x <= WALL_LENGTH; x+=dt_hor) {
        glVertex3f(x, 0, WALL_LENGTH);
        glVertex3f(x, WALL_LENGTH, WALL_LENGTH);
    }
}