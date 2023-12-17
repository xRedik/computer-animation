#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "opengl_conf.h"
#include "utils.h"
#include "boids_animation.h"

using namespace std;

float spacing;
float t = 0;

string orientationType;
string splineType;

vector<vector<float>> leader_points;
vector<vector<float>> boids_position;

// Initialize function for input values
void init()
{
    orientationType = "EulerAngle";

    leader_points ={
        {-3, 7, -8, 90, 0, 45 },
        { -1, -5, -3, 50, 40, 85, },
        {  0, -8, 0, 30, 60, 105 },
        { 1, -10, 3, 50, 40, 85 },
        { 2, -14, 6, 70, 20, 65 },
        { 3, -18, 9, 90, 0, 45 },
        { 3, -20, 12, 90, 0, 45 },
        { 6, -25, 15, 90, 0, 45 },
        { 3, -30, 18, 90, 0, 45 },
        { 6, -15, 15, 50, 40, 85, },
        { 3, -8, 9, 30, 60, 105 },
        { 1, -10, 8, 50, 40, 85 },
        { 0, -14, 6, 70, 20, 65 },
        { -1, -18, 3, 90, 0, 45 },
        { -2, -20, 0, 90, 0, 45 },
        { -3, -25, -3, 90, 0, 45 },
        { -4, -30, 6, 90, 0, 45 }          
    };

    splineType = "Catmull-Rom Spline";
    // splineType  = "B Spline";

    boids_position = {  
        {-2.5, 7.8, -5.2},
        {8.5, 8.0, -4.5},
        {3.5, 7.5, -5.5},
        {-4.0, 7.2, -5.7},
        {2.5, 8.4, -5.2},
        {4.8, 9.2, -5.0},
        {-4.2, 8.8, -5.0},
        {3.8, 11.5, -4.6},
        {0.5, 8.0, -5.2},
        {1.8, 7.2, -4.7},
        {-1.5, 7.5, -4.5},
        {9.2, 9.0, -4.0},
        {4.5, 8.0, -4.3},
        {-3.0, 7.5, -4.2},
        {3.5, 9.0, -5.0},
        {6.2, 10.5, -4.8},
        {-2.8, 9.5, -4.7},
        {4.5, 12.8, -4.3},
        {0.8, 8.5, -5.0},
        {1.5, 8.0, -4.5}
    };

    spacing = 0.005;

    init_boids(boids_position);
}

// Render function
void render()
{
    clear_buffer();

    // configuring rendering settings
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    // seting source attributes and material properties
    set_source_attributes();
    set_material_properties();
    
    // change the look at matrix
    gluLookAt(30, 30, -1, 0, 0, 0, 0, 1, 0);

    //choosing Matrix Mode and loading identity matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // calling the interpolation function with argument t and getting the computed matrix
    vector <float> leader_boid = interpolation(leader_points, splineType, orientationType, t);

    // load and animate the leader
    glPushMatrix();    
    glMultMatrixf(leader_boid.data());
    glutSolidTeapot(1);
    glPopMatrix();

    // animeate the boids
    animate_boids(leader_boid);
    
    //calculating time
    t = (t < 1.0f) ? t + spacing : 0;
    
    // reset the boids if time has reached
    if(t==0)
        init_boids(boids_position);
    
    glFlush();

    // disabling the lightening
    disable_lightening();

    // Swaping back and front buffers
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    // create opengL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 4: Behavioral Motion Control System");

    // init
    init();

    // set callback functions
    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(16, timer, 0);

    // main loop
    glutMainLoop();

    return 0;
}