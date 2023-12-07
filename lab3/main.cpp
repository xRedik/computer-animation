#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "opengl_conf.h"
#include "utils.h"
#include "balls_animation.h"

using namespace std;

// Global variables
int BALL_SIZE;
float ball_radius;
float ball_mass;

vector<vector<float>> balls_positions;
vector<vector<float>> balls_velocities;

// Initialize function for input values
void init()
{
    balls_positions = {      
        { -2.5, 8.5, 0.6 },
        { 7.0, 7.5, 1.0 },
        { 3.5, 8.2, 0.7 },
        { -5.0, 7.0, 0.8 },
        { 2.0, 8.8, 0.0 },
        { 6.0, 9.5, 0.1 },
        { -3.5, 8.5, 0.1 },
        { 3.5, 11.0, 0.5 },
        { -1.0, 8.0, 0.0 },
        { 0.5, 7.2, 0.5 },
        { -2.0, 7.5, 0.7 },
        { 8.0, 9.0, 1.1 },
        { 4.5, 8.5, 0.8 },
        { -4.0, 8.0, 0.9 },
        { 3.0, 9.5, 0.1 },
        { 5.5, 10.5, 0.2 },
        { -2.0, 9.5, 0.2 },
        { 4.5, 12.5, 0.6 },
        { 0.5, 8.8, 0.1 },
        { 1.5, 8.2, 0.6 }
    };

    balls_velocities = {
        { 1.2, 0, 0 },
        { -1.5, 0, 0 },
        { -1.2, 0, 0 },
        { 1.0, 0, 0 },
        { -1.2, 0, 0 },
        { 0.9, 0, 0 },
        { -1.3, 0, 0 },
        { 0.8, 0, 0 },
        { -1.1, 0, 0 },
        { 0.6, 0, 0 },
        { 0.9, 0, 0 },
        { -1.2, 0, 0 },
        { -1.4, 0, 0 },
        { 0.7, 0, 0 },
        { -1.0, 0, 0 },
        { 0.5, 0, 0 },
        { -1.1, 0, 0 },
        { 0.8, 0, 0 },
        { -1.2, 0, 0 },
        { 0.9, 0, 0 }
    };

    BALL_SIZE = balls_positions.size();
    
    WALL_LENGTH = 15;

    coeff_loss = 1;

    acc = {0, -9.8, 0}; //earth graviation

    dt = 0.05;

    ball_radius = 0.5;

    ball_mass = 1;

    init_balls(balls_positions, balls_velocities, ball_radius, ball_mass);
}

// Render function
void render()
{
    clear_buffer();

    // configuring rendering settings
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);

    // setting source attributes and material properties
    set_source_attributes();
    set_material_properties();

    // draw walls and animate balls
    draw_walls();
    
    animate_balls();

    // force execution of GL commands
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
    glutCreateWindow("Lab 3: Physics-Based Motion Control System by Farid Guliyev");

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