#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

// tension parameter for the Catmul Rom Spline
const float a = 0.5f;

// Catmul Rom Spline Matrix as a vector of vectors
extern vector<vector<float>> CatmulRomSplineMatrix;

// B Spline Matrix as a vector of vectors
extern vector<vector<float>> BSplineMatrix;

// function to multiply the matrices
vector<vector<float>> multiply_matrix(vector<vector<float>> &matrix_a,
                                      vector<vector<float>> &matrix_b);
                                      
// function to normalize the vector
vector<float> normalize_vector(vector<float>& v);

// function to calculate the cross product of two vectors and normalize the final vector
vector<float> cross_product_and_normalize(vector<float>& a, vector<float>& b);

// function to calculate the dot product of two vectors                           
float dot_product(vector<float>& a,vector<float>& b);

// function to display the matrix
void display_matrix(const vector<vector<float>> &matrix);

// blending function to compute T*M*G
vector<float> blending_function(vector<vector<float>> &matrix_T,
                                vector<vector<float>> &matrix_M,
                                vector<vector<float>> &matrix_G);

// fuction to flatten the 2D matrix to 1D
vector<float> flatten_matrix(vector<vector<float>> &matrix);

// function to convert quaternion to the matrix
vector<float> convert_quaternion_to_matrix(const vector<float> &vec_quat);

// function to convert eulerangle to the matrix
vector<float> convert_euler_to_matrix(const vector<float> &vec_points);

// function to interploate the leader points based on the spline type and orientation types
vector<float> interpolation(vector<vector<float>> leader_points, string splineType, string orientationType, float t);
#endif