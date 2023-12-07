
#include <cmath>
#include <vector>
#include <iostream>

#include "utils.h"

using namespace std;

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

// function to normalize the vector
vector<float> normalize_vector(vector<float>& v) {
    // throwing the error if vector does not have 3 component
    if (v.size() != 3) {
        cerr << "Error: Input vector must have three components";
        exit(1);
    }

    // calculating the magnitude of the vector
    float magnitude = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);

    // avoiding division by zero
    if (magnitude == 0.0f) {
        cerr << "Error: Cannot normalize a zero vector\n";
        return {0.0f, 0.0f, 0.0f}; 
    }

    // normalizing the vector
    vector<float> normalized_vector = {v[0] / magnitude, v[1] / magnitude, v[2] / magnitude};

    // returning the normalized vector
    return normalized_vector;
}

// function to calculate the cross product of two vectors and normalize the final vector
vector<float> cross_product_and_normalize(vector<float>& a, vector<float>& b) {
    // throwing the error if dimensions do not match
    if (a.size() != 3 || b.size() != 3) {
        cerr << "Error: Vectors must be 3-dimensional for cross product" << endl;
        cout<<a.size()<<endl;
        cout<<b.size()<<endl;
        exit(1);
    } 

    //creating the empty vector
    vector<float> result(3);

    //calculating the cross product
    result[0] = a[1] * b[2] - a[2] * b[1];
    result[1] = a[2] * b[0] - a[0] * b[2];
    result[2] = a[0] * b[1] - a[1] * b[0];

    //returning the result
    return normalize_vector(result);
}

// function to calculate the dot product of two vectors
float dot_product(vector<float>& a,vector<float>& b) {
    // throwing the error if vectors do not have 3 components
    if (a.size() != 3 || b.size() != 3) {
        cerr << "Error: Vectors must be 3-dimensional for dot product" << endl;
        exit(1);
    }

    //calculating the dot product and returning the result
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
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
vector<float> convert_quaternion(const vector<float> &vec_quat)
{
    // fetching the components from the quaternion matrix
    float w = vec_quat[0];
    float x = vec_quat[1];
    float y = vec_quat[2];
    float z = vec_quat[3];

    // defining the rotation matrix based on these components
    vector<vector<float>> rot_matrix = {
        {1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * w * z, 2 * x * z + 2 * w * y, 0},
        {2 * x * y + 2 * w * z, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * w * x, 0},
        {2 * x * z - 2 * w * y, 2 * y * z + 2 * w * x, 1 - 2 * x * x - 2 * y * y, 0},
        {0, 0, 0, 1}};

    // returning the flattened matrix of the rotation matrix
    return flatten_matrix(rot_matrix);
}