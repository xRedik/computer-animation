#include <vector>
#include "utils.h"
#include "legs.h"

using namespace std;

// initialization of the global variables
float l = -0.95f;
float tetta;

// first -> Translate Matrix 
vector<vector<float>> Translate_1 = {
    {1, 0, 0, 0},
    {0, 1, 0, l},
    {0, 0, 1, 0},
    {0, 0, 0, 1}};

// second -> Rotation Matrix definition
vector<vector<float>> Rotation_2;

// third -> Translate Matrix for left leg
vector<vector<float>> Translate_3_left_leg = {
    {1, 0, 0, 0},
    {0, 1, 0, l},
    {0, 0, 1, 0.5},
    {0, 0, 0, 1}};

// third -> Translate Matrix for right leg
vector<vector<float>> Translate_3_right_leg = {
    {1, 0, 0, 0},
    {0, 1, 0, l},
    {0, 0, 1, -0.5},
    {0, 0, 0, 1}};


// function to compute left leg matrix attached to torso
vector<float> left_leg(vector<vector<float>> torso_matrix, float t)
{

    // calculating the tetta angle for left leg 
    tetta = (float) (sin(6 * M_PI * t) * M_PI) / 4;

    // rotation matrix for left leg based on the tetta angle
    Rotation_2 = { {cos(tetta), -sin(tetta), 0, 0},
                   {sin(tetta), cos(tetta), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}
    };

    // computing the TRT for left leg
    vector<vector<float>> TL = multiply_matrix(torso_matrix, Translate_1);
    TL = multiply_matrix(TL,Rotation_2);
    TL = multiply_matrix(TL,Translate_3_left_leg);

    // returning the flattened matrix of the left leg
    return flatten_matrix(TL);
}


// function to compute right leg matrix attached to torso
vector<float> right_leg(vector<vector<float>> torso_matrix, float t)
{
    // calculating the tetta angle for right leg (negative sin because left leg is positive sin)
    tetta = - (float) (sin(6 * M_PI * t) * M_PI) / 4;

    // rotation matrix for right leg based on the tetta angle
    Rotation_2 = { {cos(tetta), -sin(tetta), 0, 0},
                   {sin(tetta), cos(tetta), 0, 0},
                   {0, 0, 1, 0},
                   {0, 0, 0, 1}
    };

    // computing the TRT for right leg
    vector<vector<float>> TR = multiply_matrix(torso_matrix, Translate_1);
    TR = multiply_matrix(TR,Rotation_2);
    TR = multiply_matrix(TR,Translate_3_right_leg);
    
    // returning the flattened matrix of the right leg
    return flatten_matrix(TR);
}


