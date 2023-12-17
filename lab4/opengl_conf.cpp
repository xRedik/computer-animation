#include <GL/glut.h>
#include <vector>

#include "opengl_conf.h"

using namespace std;

// fuction to clearing the buffer
void clear_buffer()
{
    // Clear the OpenGL buffer
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClearDepth(1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

// function for configuring lighting
void set_source_attributes()
{

    glEnable(GL_NORMALIZE);

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