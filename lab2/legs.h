#ifndef LEGS_H
#define LEGS_H
#include <vector>
#include <cmath>

using namespace std;

// function to compute left leg matrix attached to torso
vector<float> left_leg(vector<vector<float>> torso_matrix, float t);


// function to compute right leg matrix attached to torso
vector<float> right_leg(vector<vector<float>> torso_matrix, float t);

#endif