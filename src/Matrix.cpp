#include "Matrix.hpp"

// Constructors
template <typename T>
Matrix<T>::Matrix() {}

template <typename T>
Matrix<T>::Matrix(int rows, int cols) : data(rows, std::vector<T>(cols)) {}

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> input_data) : data(input_data) {}

// Accessors
template <typename T>
int Matrix<T>::rows() const
{
    return data.size();
}

template <typename T>
int Matrix<T>::cols() const
{
    return data[0].size();
}

// Element access operators
template <typename T>
std::vector<T> &Matrix<T>::operator[](int index)
{
    return data[index];
}

template <typename T>
const std::vector<T> &Matrix<T>::operator[](int index) const
{
    return data[index];
}

// Implement the rest of the member functions here...
