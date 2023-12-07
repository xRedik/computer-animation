
#include <cmath>
#include <vector>
#include <iostream>

#include "utils.h"

using namespace std;

// function to multiply the matrices
vector<vector<float>> multiply_matrix(vector<vector<float>> &matrix_a,
                                      vector<vector<float>> &matrix_b)
{

    // throwing the error if dimensions do not match
    if (matrix_a[0].size() != matrix_b.size())
    {
        cerr << "Error: Invalid dimensions" << endl;
        exit(1);
    }

    // creating the resulting function based on the input matrix dimensions
    vector<vector<float>> result(matrix_a.size(), vector<float>(matrix_b[0].size()));

    // calculating the matrix multiplication
    for (size_t i = 0; i < matrix_a.size(); ++i)
        for (size_t j = 0; j < matrix_b[0].size(); ++j)
            for (size_t k = 0; k < matrix_a[0].size(); ++k)
                result[i][j] += matrix_a[i][k] * matrix_b[k][j];

    // returning the result
    return result;
}

// function to display the matrix
void display_matrix(const vector<vector<float>> &matrix)
{
    for (const auto &row : matrix)
    {
        for (float value : row)
            cout << value << " ";
        cout << endl;
    }
    cout << endl;
}

// blending function to compute T*M*G
vector<float> blending_function(vector<vector<float>> &matrix_T,
                                vector<vector<float>> &matrix_M,
                                vector<vector<float>> &matrix_G)
{

    // multiplying the T matrix and Spline Matrix
    vector<vector<float>> TM = multiply_matrix(matrix_T, matrix_M);

    // multiplying the result matrix of the previous operation with the point matrix
    vector<vector<float>> TMG = multiply_matrix(TM, matrix_G);

    // displaying the result (if needed)
    // display_matrix(TMG);

    // returning the flattened matrix of the result matrix
    return flatten_matrix(TMG);
}

// fuction to flatten the 2D matrix to 1D
vector<float> flatten_matrix(vector<vector<float>> &matrix)
{
    vector<float> flattenedMatrix;

    // transposing the matrix
    vector<vector<float>> transposedMatrix(matrix[0].size(), vector<float>(matrix.size()));
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[i].size(); ++j) {
            transposedMatrix[j][i] = matrix[i][j];
        }
    }

    // flattening the transposed matrix
    for (const auto& row : transposedMatrix) {
        flattenedMatrix.insert(flattenedMatrix.end(), row.begin(), row.end());
    }

    // returning the flattened matrix
    return flattenedMatrix;
}

// function to convert quaternion to the matrix
vector<float> convert_quaternion_to_matrix(const vector<float> &vec_points)
{
    // fetching the components from the quaternion matrix
    float w = vec_points[3];
    float x = vec_points[4];
    float y = vec_points[5];
    float z = vec_points[6];

    // defining the complete matrix based on these components
    vector<vector<float>> complete_matrix = {
        {1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, vec_points[0]},
        {2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x, vec_points[1]},
        {2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y, vec_points[2]},
        {0, 0, 0, 1}};

    // returning the flattened matrix of the rotation matrix
    return flatten_matrix(complete_matrix);
}

// function to convert eulerangle to the matrix
vector<float> convert_euler_to_matrix(const vector<float> &vec_points)
{
    // fetching and converting angles to the radians
    float x = vec_points[3] * (M_PI / 180.0f);
    float y = vec_points[4] * (M_PI / 180.0f);
    float z = vec_points[5] * (M_PI / 180.0f);

    // defining the complete matrix based on these components
    vector<vector<float>> complete_matrix = {
        {cos(y) * cos(z), -cos(y) * sin(z), sin(y), vec_points[0]},
        {cos(x) * sin(z) + sin(x) * cos(z) * sin(y), cos(x) * cos(z) - sin(x) * sin(z) * sin(y), -sin(x) * cos(y), vec_points[1]},
        {sin(x) * sin(z) - cos(x) * cos(z) * sin(y), sin(x) * cos(z) + cos(x) * sin(z) * sin(y), cos(x) * cos(y), vec_points[2]},
        {0, 0, 0, 1}
    };

    // returning the flattened matrix of the complete matrix
    return flatten_matrix(complete_matrix);
}

