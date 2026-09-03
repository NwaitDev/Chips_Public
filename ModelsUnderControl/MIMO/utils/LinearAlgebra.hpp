/**
 * @file LinearAlgebra.hpp
 * 
 * @brief Linear algebra utilities for MIMO controller implementation
 */

#ifndef LINEAR_ALGEBRA_HPP
#define LINEAR_ALGEBRA_HPP

#include <vector>
#include <cmath>
#include <stdexcept>
#include <limits>

namespace linalg {

using Vec = std::vector<double>;
using Mat = std::vector<double>; // row-major storage, size = rows*cols

/**
 * @brief Creates a matrix of zeros with the given dimensions
 * 
 * @param rows Number of rows
 * @param cols Number of columns
 * @return Mat Matrix filled with zeros
 */
inline Mat zeros(int rows, int cols) {
    return Mat(static_cast<size_t>(rows) * static_cast<size_t>(cols), 0.0);
}

/**
 * @brief Creates an identity matrix of size n x n
 * 
 * @param n Size of the identity matrix
 * @return Mat Identity matrix
 */
inline Mat identity(int n) {
    Mat I = zeros(n, n);
    for (int i = 0; i < n; ++i) {
        I[static_cast<size_t>(i) * static_cast<size_t>(n) + static_cast<size_t>(i)] = 1.0;
    }
    return I;
}

/**
 * @brief Returns a reference to an element in a matrix
 * 
 * @param M    Matrix
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @param r    Row index
 * @param c    Column index
 * @return double& Reference to the element at (r, c)
 */
inline double& at(Mat& M, int rows, int cols, int r, int c) {
    (void)rows; (void)cols;
    return M[static_cast<size_t>(r) * static_cast<size_t>(cols) + static_cast<size_t>(c)];
}

/**
 * @brief Returns a const reference to an element in a matrix
 * 
 * @param M    Matrix
 * @param rows Number of rows in the matrix
 * @param cols Number of columns in the matrix
 * @param r    Row index
 * @param c    Column index
 * @return double Value of the element at (r, c)
 */
inline double at(const Mat& M, int rows, int cols, int r, int c) {
    (void)rows; (void)cols;
    return M[static_cast<size_t>(r) * static_cast<size_t>(cols) + static_cast<size_t>(c)];
}

/**
 * @brief Returns the transpose of a matrix
 * 
 * @param A    Matrix to transpose
 * @param rows Number of rows in the original matrix
 * @param cols Number of columns in the original matrix
 * @return Mat Transposed matrix
 */
inline Mat transpose(const Mat& A, int rows, int cols) {
    Mat T = zeros(cols, rows);
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            at(T, cols, rows, c, r) = at(A, rows, cols, r, c);
        }
    }
    return T;
}

/**
 * @brief Adds two matrices element-wise
 * 
 * @param A First matrix
 * @param B Second matrix
 * @return Mat Sum of the two matrices
 */
inline Mat add(const Mat& A, const Mat& B) {
    if (A.size() != B.size()) throw std::runtime_error("add: size mismatch");
    Mat C(A.size());
    for (size_t i = 0; i < A.size(); ++i) C[i] = A[i] + B[i];
    return C;
}

/**
 * @brief Subtracts two matrices element-wise
 * 
 * @param A First matrix
 * @param B Second matrix
 * @return Mat Difference of the two matrices
 */
inline Mat sub(const Mat& A, const Mat& B) {
    if (A.size() != B.size()) throw std::runtime_error("sub: size mismatch");
    Mat C(A.size());
    for (size_t i = 0; i < A.size(); ++i) C[i] = A[i] - B[i];
    return C;
}

/**
 * @brief Multiplies two matrices
 * 
 * @param A     First matrix
 * @param aRows Number of rows in first matrix
 * @param aCols Number of columns in first matrix
 * @param B     Second matrix
 * @param bRows Number of rows in second matrix
 * @param bCols Number of columns in second matrix
 * @return Mat Product of the two matrices
 */
inline Mat mul(const Mat& A, int aRows, int aCols, const Mat& B, int bRows, int bCols) {
    if (aCols != bRows) throw std::runtime_error("mul: dimension mismatch");
    Mat C = zeros(aRows, bCols);
    for (int i = 0; i < aRows; ++i) {
        for (int k = 0; k < aCols; ++k) {
            const double aik = at(A, aRows, aCols, i, k);
            for (int j = 0; j < bCols; ++j) {
                at(C, aRows, bCols, i, j) += aik * at(B, bRows, bCols, k, j);
            }
        }
    }
    return C;
}

/**
 * @brief Multiplies a matrix with a vector
 * 
 * @param A     Matrix
 * @param aRows Number of rows in the matrix
 * @param aCols Number of columns in the matrix
 * @param x     Vector to multiply with
 * @return Vec Result of the multiplication
 */
inline Vec mul(const Mat& A, int aRows, int aCols, const Vec& x) {
    if (static_cast<int>(x.size()) != aCols) throw std::runtime_error("mul(A,x): dimension mismatch");
    Vec y(static_cast<size_t>(aRows), 0.0);
    for (int i = 0; i < aRows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < aCols; ++j) {
            sum += at(A, aRows, aCols, i, j) * x[static_cast<size_t>(j)];
        }
        y[static_cast<size_t>(i)] = sum;
    }
    return y;
}

/**
 * @brief Returns the Frobenius norm of a matrix
 * 
 * @param A Matrix
 * @return double Frobenius norm of the matrix
 */
inline double normF(const Mat& A) {
    double s = 0.0;
    for (double v : A) s += v * v;
    return std::sqrt(s);
}

/**
 * @brief Returns the inverse of a matrix
 * 
 * @param A Matrix to invert
 * @param n Size of the square matrix
 * @return Mat Inverse of the matrix
 */
inline Mat inv(const Mat& A, int n) {
    // Gauss-Jordan inversion (n x n)
    Mat aug = zeros(n, 2 * n);

    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            at(aug, n, 2 * n, r, c) = at(A, n, n, r, c);
        }
        at(aug, n, 2 * n, r, n + r) = 1.0;
    }

    for (int col = 0; col < n; ++col) {
        // Pivot selection
        int pivot = col;
        double best = std::fabs(at(aug, n, 2 * n, col, col));
        for (int r = col + 1; r < n; ++r) {
            double v = std::fabs(at(aug, n, 2 * n, r, col));
            if (v > best) {
                best = v;
                pivot = r;
            }
        }

        if (best < 1e-12) throw std::runtime_error("inv: singular matrix");

        if (pivot != col) {
            for (int c = 0; c < 2 * n; ++c) {
                std::swap(at(aug, n, 2 * n, col, c), at(aug, n, 2 * n, pivot, c));
            }
        }

        const double diag = at(aug, n, 2 * n, col, col);
        for (int c = 0; c < 2 * n; ++c) {
            at(aug, n, 2 * n, col, c) /= diag;
        }

        for (int r = 0; r < n; ++r) {
            if (r == col) continue;
            const double factor = at(aug, n, 2 * n, r, col);
            if (std::fabs(factor) < 1e-18) continue;
            for (int c = 0; c < 2 * n; ++c) {
                at(aug, n, 2 * n, r, c) -= factor * at(aug, n, 2 * n, col, c);
            }
        }
    }

    Mat Ainv = zeros(n, n);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            at(Ainv, n, n, r, c) = at(aug, n, 2 * n, r, n + c);
        }
    }
    return Ainv;
}

} 

#endif
