#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <type_traits>
#include <cmath>

// Concept for Matrix Element
template <typename T>
concept MatrixElement = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>; // Addition must be defined for elements
    { a - b } -> std::convertible_to<T>; // Subtraction must be defined for elements
    { a * b } -> std::convertible_to<T>; // Multiplication must be defined for elements
    { b / a } -> std::convertible_to<T>; // Division must be defined for elements
};

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>; // Concept for arithmetic types

// Matrix Class
template <MatrixElement T>
class Matrix
{
private:
    std::vector<std::vector<T>> data;

public:
    // Constructors
    Matrix() {} // Default constructor

    Matrix(int rows, int cols) : data(rows, std::vector<T>(cols)) {} // Constructor with specified rows and columns

    Matrix(std::vector<std::vector<T>> input_data) : data(input_data) {} // Constructor with initial data

    // Accessors
    int rows() const { return data.size(); }

    int cols() const { return data[0].size(); }

    // Element access operators
    std::vector<T> &operator[](int index) { return data[index]; }

    const std::vector<T> &operator[](int index) const { return data[index]; }

    // Matrix operations
    Matrix<T> operator+(const Matrix<T> &other) const
    {
        if (rows() != other.rows() || cols() != other.cols())
        {
            throw std::runtime_error("Matrices must have the same dimensions.");
        }
        Matrix<T> result(rows(), cols());
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < cols(); ++j)
            {
                result[i][j] = data[i][j] + other[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T> &other) const
    {
        if (rows() != other.rows() || cols() != other.cols())
        {
            throw std::runtime_error("Matrices must have the same dimensions.");
        }
        Matrix<T> result(rows(), cols());
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < cols(); ++j)
            {
                result[i][j] = data[i][j] - other[i][j];
            }
        }
        return result;
    }

    Matrix<T> operator*(const Matrix<T> &other) const
    {
        if (cols() != other.rows())
        {
            throw std::runtime_error("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        Matrix<T> result(rows(), other.cols());
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < other.cols(); ++j)
            {
                for (int k = 0; k < cols(); ++k)
                {
                    result[i][j] += data[i][k] * other[k][j];
                }
            }
        }
        return result;
    }

    // Scalar multiplication
    Matrix<T> operator*(T scalar) const
    {
        Matrix<T> result(rows(), cols());
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < cols(); ++j)
            {
                result[i][j] = data[i][j] * scalar;
            }
        }
        return result;
    }

    // Inverse of a matrix
    Matrix<T> inverse() const
    {
        if (rows() != cols())
        {
            throw std::runtime_error("Matrix must be square.");
        }
        // Implementation of matrix inversion goes here
    }

    // Other operations
    Matrix<T> submatrix(int row, int col) const
    {
        Matrix<T> sub(rows() - 1, cols() - 1);
        int subrow = 0, subcol = 0;
        for (int i = 0; i < rows(); ++i)
        {
            if (i != row)
            {
                for (int j = 0; j < cols(); ++j)
                {
                    if (j != col)
                    {
                        sub[subrow][subcol] = data[i][j];
                        subcol++;
                    }
                }
                subrow++;
                subcol = 0;
            }
        }
        return sub;
    }

    Matrix<T> transpose() const
    {
        Matrix<T> transpose(cols(), rows());
        for (int i = 0; i < rows(); ++i)
        {
            for (int j = 0; j < cols(); ++j)
            {
                transpose[j][i] = data[i][j];
            }
        }
        return transpose;
    }

    T determinant() const
    {
        if (rows() != cols())
        {
            throw std::runtime_error("Matrix must be square.");
        }
        if (rows() == 1)
        {
            return data[0][0];
        }
        if (rows() == 2)
        {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }
        T det = 0;
        for (int i = 0; i < cols(); ++i)
        {
            det += (i % 2 == 0 ? 1 : -1) * data[0][i] * submatrix(0, i).determinant();
        }
        return det;
    }

    // Identity matrix generation
    static Matrix<T> identity(int size)
    {
        Matrix<T> identityMatrix(size, size);
        for (int i = 0; i < size; ++i)
        {
            identityMatrix[i][i] = 1; // Diagonal elements are 1
        }
        return identityMatrix;
    }

    // Matrix power
    Matrix<T> power(int exponent) const
    {
        if (rows() != cols())
        {
            throw std::runtime_error("Matrix must be square.");
        }
        if (exponent < 0)
        {
            throw std::runtime_error("Exponent must be non-negative.");
        }
        if (exponent == 0)
        {
            return Matrix<T>::identity(rows()); // Identity matrix
        }
        if (exponent == 1)
        {
            return *this; // Return the matrix itself
        }
        Matrix<T> result = *this;
        for (int i = 1; i < exponent; ++i)
        {
            result = result * (*this);
        }
        return result;
    }

    // Output operator
    friend std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows(); ++i)
        {
            for (int j = 0; j < matrix.cols(); ++j)
            {
                os << std::fixed << std::setprecision(2) << matrix[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }
};

#endif // MATRIX_H
