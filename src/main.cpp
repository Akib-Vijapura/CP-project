#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>
#include <type_traits>
#include <cmath>
using namespace std;

// Concept for Matrix Element
template <typename T>
concept MatrixElement = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>; // Addition must be defined for elements
    { a - b } -> std::convertible_to<T>; // Subtraction must be defined for elements
    { a *b } -> std::convertible_to<T>;  // Multiplication must be defined for elements
    { b / a } -> std::convertible_to<T>; // Division must be defined for elements
};

template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>; // Concept for arithmetic types

// Matrix Class
template <MatrixElement T>
class Matrix
{
private:
    vector<vector<T>> data;

public:
    // Constructors
    Matrix() {} // Default constructor

    Matrix(int rows, int cols) : data(rows, vector<T>(cols)) {}

    Matrix(vector<vector<T>> input_data) : data(input_data) {}

    // Accessors
    int rows() const { return data.size(); }

    int cols() const { return data[0].size(); }

    // Element access operators
    vector<T> &operator[](int index) { return data[index]; }

    const vector<T> &operator[](int index) const { return data[index]; }

    // Matrix operations
    Matrix<T> operator+(const Matrix<T> &other) const
    {
        if (rows() != other.rows() || cols() != other.cols())
        {
            throw runtime_error("Matrices must have the same dimensions.");
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
            throw runtime_error("Matrices must have the same dimensions.");
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
            throw runtime_error("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
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
            throw runtime_error("Matrix must be square.");
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
            throw runtime_error("Matrix must be square.");
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
            throw runtime_error("Matrix must be square.");
        }
        if (exponent < 0)
        {
            throw runtime_error("Exponent must be non-negative.");
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
    friend ostream &operator<<(ostream &os, const Matrix<T> &matrix)
    {
        for (int i = 0; i < matrix.rows(); ++i)
        {
            for (int j = 0; j < matrix.cols(); ++j)
            {
                os << fixed << setprecision(2) << matrix[i][j] << " ";
            }
            os << endl;
        }
        return os;
    }
};

int main()
{
    cout << "Matrix Calculator" << endl;
    cout << "1. Add Matrices" << endl;
    cout << "2. Subtract Matrices" << endl;
    cout << "3. Multiply Matrices" << endl;
    cout << "4. Find Determinant" << endl;
    cout << "5. Find Transpose" << endl;
    cout << "6. Scalar Multiplication" << endl;
    cout << "7. Generate Identity Matrix" << endl;
    cout << "8. Matrix Power" << endl;

    int choice;
    cout << "Enter your choice (1-8): ";
    cin >> choice;

    switch (choice)
    {
    case 1:
    case 2:
    case 3:
    {
        int rows1, cols1, rows2, cols2;
        cout << "Enter the number of rows for the first matrix: ";
        cin >> rows1;
        cout << "Enter the number of columns for the first matrix: ";
        cin >> cols1;
        Matrix<double> matrix1(rows1, cols1);
        cout << "Enter the elements of the first matrix:" << endl;
        for (int i = 0; i < rows1; ++i)
        {
            for (int j = 0; j < cols1; ++j)
            {
                cin >> matrix1[i][j];
            }
        }

        cout << "Enter the number of rows for the second matrix: ";
        cin >> rows2;
        cout << "Enter the number of columns for the second matrix: ";
        cin >> cols2;
        Matrix<double> matrix2(rows2, cols2);
        cout << "Enter the elements of the second matrix:" << endl;
        for (int i = 0; i < rows2; ++i)
        {
            for (int j = 0; j < cols2; ++j)
            {
                cin >> matrix2[i][j];
            }
        }

        Matrix<double> result;
        if (choice == 1)
            result = matrix1 + matrix2;
        else if (choice == 2)
            result = matrix1 - matrix2;
        else if (choice == 3)
            result = matrix1 * matrix2;

        cout << "Result:" << endl;
        cout << result;
        break;
    }
    case 4:
    {
        int rows, cols;
        cout << "Enter the number of rows for the matrix: ";
        cin >> rows;
        cout << "Enter the number of columns for the matrix: ";
        cin >> cols;
        Matrix<double> matrix(rows, cols);
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cin >> matrix[i][j];
            }
        }

        double det = matrix.determinant();
        cout << "Determinant: " << fixed << setprecision(2) << det << endl;
        break;
    }
    case 5:
    {
        int rows, cols;
        cout << "Enter the number of rows for the matrix: ";
        cin >> rows;
        cout << "Enter the number of columns for the matrix: ";
        cin >> cols;
        Matrix<double> matrix(rows, cols);
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cin >> matrix[i][j];
            }
        }

        Matrix<double> transpose = matrix.transpose();
        cout << "Transpose:" << endl;
        cout << transpose;
        break;
    }
    case 6:
    {
        int rows, cols;
        double scalar;
        cout << "Enter the number of rows for the matrix: ";
        cin >> rows;
        cout << "Enter the number of columns for the matrix: ";
        cin >> cols;
        cout << "Enter the scalar value: ";
        cin >> scalar;
        Matrix<double> matrix(rows, cols);
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cin >> matrix[i][j];
            }
        }

        Matrix<double> result = matrix * scalar;
        cout << "Result:" << endl;
        cout << result;
        break;
    }
    case 7:
    {
        int size;
        cout << "Enter the size of the identity matrix: ";
        cin >> size;
        Matrix<double> identityMatrix = Matrix<double>::identity(size);
        cout << "Identity Matrix:" << endl;
        cout << identityMatrix;
        break;
    }
    case 8:
    {
        int rows, cols, exponent;
        cout << "Enter the number of rows for the matrix: ";
        cin >> rows;
        cout << "Enter the number of columns for the matrix: ";
        cin >> cols;
        Matrix<double> matrix(rows, cols);
        cout << "Enter the elements of the matrix:" << endl;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                cin >> matrix[i][j];
            }
        }
        cout << "Enter the exponent: ";
        cin >> exponent;
        Matrix<double> result = matrix.power(exponent);
        cout << "Result:" << endl;
        cout << result;
        break;
    }
    default:
        cout << "Invalid choice. Please try again." << endl;
        break;
    }

    return 0;
}
