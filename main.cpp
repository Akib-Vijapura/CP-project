#include <iostream>
#include <vector>
#include <stdexcept>

template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t rows, size_t cols) : rows(rows), cols(cols)
    {
        data.resize(rows, std::vector<T>(cols, T()));
    }

    Matrix(size_t rows, size_t cols, const T &initial) : rows(rows), cols(cols)
    {
        data.resize(rows, std::vector<T>(cols, initial));
    }

    size_t numRows() const
    {
        return rows;
    }

    size_t numCols() const
    {
        return cols;
    }

    T &operator()(size_t row, size_t col)
    {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Index out of range");
        return data[row][col];
    }

    const T &operator()(size_t row, size_t col) const
    {
        if (row >= rows || col >= cols)
            throw std::out_of_range("Index out of range");
        return data[row][col];
    }

    Matrix<T> operator+(const Matrix<T> &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions do not match");

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j] + other(i, j);
            }
        }
        return result;
    }

    Matrix<T> operator-(const Matrix<T> &other) const
    {
        if (rows != other.rows || cols != other.cols)
            throw std::invalid_argument("Matrix dimensions do not match");

        Matrix<T> result(rows, cols);
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                result(i, j) = data[i][j] - other(i, j);
            }
        }
        return result;
    }

    template <typename U>
    friend Matrix<U> operator*(const Matrix<U> &a, const Matrix<U> &b);

    template <typename U>
    friend Matrix<U> operator*(const Matrix<U> &matrix, const U &scalar);

    template <typename U>
    friend Matrix<U> operator*(const U &scalar, const Matrix<U> &matrix);

    template <typename U>
    friend std::ostream &operator<<(std::ostream &os, const Matrix<U> &matrix);
};

template <typename T>
Matrix<T> operator*(const Matrix<T> &a, const Matrix<T> &b)
{
    if (a.cols != b.rows)
        throw std::invalid_argument("Matrix dimensions do not match");

    Matrix<T> result(a.rows, b.cols);
    for (size_t i = 0; i < a.rows; ++i)
    {
        for (size_t j = 0; j < b.cols; ++j)
        {
            for (size_t k = 0; k < a.cols; ++k)
            {
                result(i, j) += a(i, k) * b(k, j);
            }
        }
    }
    return result;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &matrix, const T &scalar)
{
    Matrix<T> result(matrix.rows, matrix.cols);
    for (size_t i = 0; i < matrix.rows; ++i)
    {
        for (size_t j = 0; j < matrix.cols; ++j)
        {
            result(i, j) = matrix(i, j) * scalar;
        }
    }
    return result;
}

template <typename T>
Matrix<T> operator*(const T &scalar, const Matrix<T> &matrix)
{
    return matrix * scalar;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const Matrix<T> &matrix)
{
    for (size_t i = 0; i < matrix.numRows(); ++i)
    {
        for (size_t j = 0; j < matrix.numCols(); ++j)
        {
            os << matrix(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

int main()
{
    int choice;
    std::cout << "Choose the operation to perform:" << std::endl;
    std::cout << "1. Matrix Addition" << std::endl;
    std::cout << "2. Matrix Subtraction" << std::endl;
    std::cout << "3. Matrix Multiplication" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    size_t rows, cols;
    std::cout << "Enter the number of rows and columns for matrices: ";
    std::cin >> rows >> cols;

    Matrix<double> A(rows, cols);
    Matrix<double> B(rows, cols);

    std::cout << "Enter elements of matrix A:" << std::endl;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            std::cin >> A(i, j);
        }
    }

    std::cout << "Enter elements of matrix B:" << std::endl;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            std::cin >> B(i, j);
        }
    }

    Matrix<double> result(rows, cols); // Initialize result matrix with appropriate dimensions

    switch (choice)
    {
    case 1:
        result = A + B;
        std::cout << "Matrix Addition Result:" << std::endl;
        break;
    case 2:
        result = A - B;
        std::cout << "Matrix Subtraction Result:" << std::endl;
        break;
    case 3:
        result = A * B;
        std::cout << "Matrix Multiplication Result:" << std::endl;
        break;
    default:
        std::cerr << "Invalid choice!" << std::endl;
        return 1;
    }

    std::cout << result << std::endl;

    return 0;
}
