#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "opengl_conf.h"
#include "utils.h"
#include "legs.h"

using namespace std;

// Global variables
float spacing;
int INPUT_SIZE;

string splineType;

vector<vector<float>> input;
vector<float> position;
vector<vector<float>> torso_matrix;
float t = 0.0f;

// declaration of the interpolation function
vector<float> interpolation(float t);

// Initialize function for input values
void init()
{
    input = {{5, 0, -20},
             {-5, 0, -20},
             {-4, 0, -10},
             {4, 0, -10}, 
             {3, 0, -5},
             {-3, 0, -5},
             {1, 0, -3}};

    splineType = "Catmull-Rom Spline";
    // splineType  = "B Spline";

    spacing = 0.005;

    INPUT_SIZE = input.size();
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

    // setting matrix mode to modelview and loading the identity
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // getting the 1D torso matrix from interpolation function
    vector<float> torso_movement = interpolation(t);

    // loading the 1D torso matrix with scaled solid cube
    glLoadMatrixf(torso_movement.data());
    glScalef(0.7f, 2.0f, 0.3f);
    glutSolidCube(1);

    // getting the left leg attached to torso
    vector<float> left_leg_matrix = left_leg(torso_matrix, t);
    
    //loading the left leg matrix with scaled solid cube
    glLoadMatrixf(left_leg_matrix.data());
    glScalef(0.3f, 2.0f, 0.3);
    glutSolidCube(1);

    // getting the right leg attached to torso
    vector<float> right_movement = right_leg(torso_matrix, t);
    glLoadMatrixf(right_movement.data());
    
    //loading the right leg matrix with scaled solid cube
    glScalef(0.3f, 2.0f, 0.3);
    glutSolidCube(1);

    // calculating the new time
    t = (t < 1.0f) ? t + spacing : 0.0f;

    // force execution of GL commands
    glFlush();

    // disabling the lightening
    disable_lightening();

    // Swaping back and front buffers
    glutSwapBuffers();
}

// Interpolation function
vector<float> interpolation(float t)
{
    // calculating the current i
    int i = t * (INPUT_SIZE - 1);

    // lambda function for retrieving the position components from a specified circular point in the input vector.
    auto get_pos_point = [&](int index, int offset) -> vector<float>
    {
        return vector<float>(input[(index + offset + INPUT_SIZE) % INPUT_SIZE].begin(),
                             input[(index + offset + INPUT_SIZE) % INPUT_SIZE].begin() + 3);
    };

    // combining the position point vectors to one 2D vector
    vector<vector<float>> position_points = {
        get_pos_point(i, -1 + INPUT_SIZE),
        get_pos_point(i, 0),
        get_pos_point(i, 1),
        get_pos_point(i, 2),
    };

    // calculating the current t
    t = t * (INPUT_SIZE - 1) - i;

    // creating the T matrix based on that value
    vector<vector<float>> Tmatrix = {{t * t * t, t * t, t, 1}};

    // callling the blending function for position based on the spline type
    if (!splineType.compare("Catmull-Rom Spline"))
        position = blending_function(Tmatrix, CatmulRomSplineMatrix, position_points);
    else if (!splineType.compare("B Spline"))
        position = blending_function(Tmatrix, BSplineMatrix, position_points);
    else
    {
        // throwing an error if Spline Type is wrong and terminating the program
        cerr << "Wrong Spline Type" << endl;
        exit(1);
    }

    // initialization of the torso matrix
    torso_matrix = {
        {1, 0, 0, position[0]},
        {0, 1, 0, position[1]},
        {0, 0, 1, position[2]},
        {0, 0, 0, 1},
    };

    // returning the 1D version of torso matrix
    return flatten_matrix(torso_matrix);
}

int main(int argc, char **argv)
{
    // create opengL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 2: Hierarchical Object Motion Control System by Farid Guliyev");

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