#include <GL/glut.h>
#include <cmath>
#include <vector>
#include <iostream>

#include "opengl_conf.h"
#include "utils.h"

using namespace std;

float spacing;
int INPUT_SIZE;
float t = 0.0f;

string orientationType;
string splineType;

vector<vector<float>> input;
vector<float> blended_points;

// tension parameter for the Catmul Rom Spline
const float a = 0.5f;

// Catmul Rom Spline Matrix as a vector of vectors
vector<vector<float>> CatmulRomSplineMatrix = {
    {-a, 2.0f - a, a - 2.0f, a},
    {2.0f * a, a - 3.0f, 3.0f - 2.0f * a, -a},
    {-a, 0.0f, a, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f}};

// B Spline Matrix as a vector of vectors
vector<vector<float>> BSplineMatrix = {
    {-1.0f / 6, 3.0f / 6, -3.0f / 6, 1.0f / 6},
    {3.0f / 6, -6.0f / 6, 3.0f / 6, 0.0f},
    {-3.0f / 6, 0.0f, 3.0f / 6, 0.0f},
    {1.0f / 6, 4.0f / 6, 1.0f / 6, 0.0f}};

// declaration of the interpolation function
vector <float> interpolation(float t);

// Initialize function for input values
void init()
{
    // orientationType = "EulerAngle";

    // input = {
    //     {3, 2, -10, 60, 0, 45},
    //     {1, 0, -10, 30, 45, 0},
    //     {-1, 1, -20, 0, 90, -60},
    //     {-3, 2, -9, -90, 60, 0},
    //     {1, 0, -7, 35, 0, 50}};

    orientationType = "Quaternion";

    input = {{1, 1, -15, 1, 0, 0, 0},
             {4, 4, -20, 0.707, 0, 0.707, 0},
             {-5, 0, -15, 0.707, 0.707, 0, 0},
             {-5, 5, -15, 0.5, 0.5, -0.5, -0.5},
             {-1, 1, -15, 0.707, 0, 0.707, 0},
             {1, 5, -35, 0.5, -0.5, 0.5, -0.5},
             {0, 0, -5, 0.707, 0, 0.707, 0},
             {1, 1, -15, 1, 0, 0, 0}};

    splineType = "Catmull-Rom Spline";
    // splineType  = "B Spline";

    spacing = 0.005f;

    INPUT_SIZE = input.size();
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

    //choosing Matrix Mode and loading itentity
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // calling the interpolation function with argument t and getting the computed matrix
    vector <float> computed_matrix = interpolation(t);

    // loading the matrix and teapot
    glLoadMatrixf(computed_matrix.data());

    glutSolidTeapot(1);

    //calculating time
    t = (t < 1.0f) ? t + spacing : 0.0f;

    glFlush();

    // disabling the lightening
    disable_lightening();

    // Swaping back and front buffers
    glutSwapBuffers();
}

// general Interpolation function
vector<float> interpolation(float t)
{
    // calculating the current i
    int i = t * (INPUT_SIZE - 1);

    // lambda function for retrieving the points from input
    auto get_points = [&](int index, int offset) -> vector<float>
    {
        return vector<float>(input[(index + offset + INPUT_SIZE) % INPUT_SIZE].begin(),
                             input[(index + offset + INPUT_SIZE) % INPUT_SIZE].end());
    };

    // combining the point vectorss to one 2D vector
    vector<vector<float>> choosen_points = {
        get_points(i, -1 + INPUT_SIZE),
        get_points(i, 0),
        get_points(i, 1),
        get_points(i, 2),
    };

    // calculating the current t and creating the T matrix based on that value
    t = t * (INPUT_SIZE - 1) - i;
    
    vector<vector<float>> Tmatrix = {{t * t * t, t * t, t, 1}};

    // callling the blending function for points based on the spline type
    if (!splineType.compare("Catmull-Rom Spline"))
        blended_points = blending_function(Tmatrix, CatmulRomSplineMatrix, choosen_points);
    else if (!splineType.compare("B Spline"))
        blended_points = blending_function(Tmatrix, BSplineMatrix, choosen_points);
    else
    {
        // throwing an error if Spline Type is wrong and terminating the program
        cerr << "Error: Wrong Spline Type" << endl;
        exit(1);
    }

    // convert euler or quaternion to the completed final matrix with corresponding blended_points and orientation
    if(!orientationType.compare("EulerAngle"))
        return convert_euler_to_matrix(blended_points);
    else if(!orientationType.compare("Quaternion"))
        return convert_quaternion_to_matrix(blended_points);

    // throw an error if orientation type is wrong and terminate the program
    cerr<<"Error: Wrong Orientation Type. Should be EulerAngle or Quaternion"<<endl;
    exit(1);
}

int main(int argc, char **argv)
{
    // create opengL window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Lab 1: Basic Key Framing by Farid Guliyev");

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