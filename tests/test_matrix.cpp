#include <iostream>
#include <vector>
#include <cassert>  // for assert
#include "../src/Matrix.cpp" // assuming Matrix class is declared in Matrix.h

using namespace std;

void testMatrixCreation()
{
    // Test default constructor
    Matrix<double> mat1;

    // Test constructor with specified rows and columns
    Matrix<double> mat2(3, 3);

    // Test constructor with initial data
    vector<vector<double>> initial_data = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    Matrix<double> mat3(initial_data);

    // Test rows and cols functions
    assert(mat1.rows() == 0);
    assert(mat1.cols() == 0);
    assert(mat2.rows() == 3);
    assert(mat2.cols() == 3);
    assert(mat3.rows() == 3);
    assert(mat3.cols() == 3);

    // Test element access
    assert(mat3[1][1] == 5);
}

void testMatrixOperations()
{
    // Test matrix addition
    Matrix<double> mat1({{1, 2}, {3, 4}});
    Matrix<double> mat2({{5, 6}, {7, 8}});
    Matrix<double> add_result = mat1 + mat2;
    assert(add_result[0][0] == 6 && add_result[0][1] == 8);
    assert(add_result[1][0] == 10 && add_result[1][1] == 12);

    // Test matrix subtraction
    Matrix<double> sub_result = mat1 - mat2;
    assert(sub_result[0][0] == -4 && sub_result[0][1] == -4);
    assert(sub_result[1][0] == -4 && sub_result[1][1] == -4);

    // Test matrix multiplication
    Matrix<double> mul_result = mat1 * mat2;
    assert(mul_result[0][0] == 19 && mul_result[0][1] == 22);
    assert(mul_result[1][0] == 43 && mul_result[1][1] == 50);
}

void testDeterminant()
{
    // Test determinant calculation
    Matrix<double> mat({{1, 2}, {3, 4}});
    double det = mat.determinant();
    assert(det == -2);
}

void testTranspose()
{
    // Test transpose operation
    Matrix<double> mat({{1, 2}, {3, 4}});
    Matrix<double> transpose_result = mat.transpose();
    assert(transpose_result[0][0] == 1 && transpose_result[0][1] == 3);
    assert(transpose_result[1][0] == 2 && transpose_result[1][1] == 4);
}

void testScalarMultiplication()
{
    // Test scalar multiplication
    Matrix<double> mat({{1, 2}, {3, 4}});
    Matrix<double> scalar_result = mat * 2;
    assert(scalar_result[0][0] == 2 && scalar_result[0][1] == 4);
    assert(scalar_result[1][0] == 6 && scalar_result[1][1] == 8);
}

void testIdentityMatrix()
{
    // Test identity matrix generation
    Matrix<double> identity = Matrix<double>::identity(3);
    assert(identity[0][0] == 1 && identity[0][1] == 0 && identity[0][2] == 0);
    assert(identity[1][0] == 0 && identity[1][1] == 1 && identity[1][2] == 0);
    assert(identity[2][0] == 0 && identity[2][1] == 0 && identity[2][2] == 1);
}

void testMatrixPower()
{
    // Test matrix power
    Matrix<double> mat({{1, 2}, {3, 4}});
    Matrix<double> power_result = mat.power(2);
    assert(power_result[0][0] == 7 && power_result[0][1] == 10);
    assert(power_result[1][0] == 15 && power_result[1][1] == 22);
}

int main()
{
    // Run tests
    testMatrixCreation();
    testMatrixOperations();
    testDeterminant();
    testTranspose();
    testScalarMultiplication();
    testIdentityMatrix();
    testMatrixPower();

    cout << "All tests passed!" << endl;
    return 0;
}
