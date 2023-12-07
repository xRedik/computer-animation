#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

// function to multiply the matrices
vector<vector<float>> multiply_matrix(vector<vector<float>> &matrix_a,
                                      vector<vector<float>> &matrix_b);

// function to display the matrix
void display_matrix(const vector<vector<float>> &matrix);

// blending function to compute T*M*G
vector<float> blending_function(vector<vector<float>> &matrix_T,
                                vector<vector<float>> &matrix_M,
                                vector<vector<float>> &matrix_G);

// fuction to flatten the 2D matrix to 1D
vector<float> flatten_matrix(vector<vector<float>> &matrix);

// function to convert quaternion to the matrix
vector<float> convert_quaternion_to_matrix(const vector<float> &vec_points);

// function to convert eulerangle to the matrix
vector<float> convert_euler_to_matrix(const vector<float> &vec_points);
#endif