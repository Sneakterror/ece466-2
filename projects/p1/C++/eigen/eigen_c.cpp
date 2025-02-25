#include "eigen_c.h"
#include <Eigen/Dense>
#include <iostream>
#include <random>


struct EigenMatrix {
  Eigen::MatrixXd mat;
  
  EigenMatrix(int rows, int cols) : mat(rows, cols) { mat.setZero(); }
  EigenMatrix(const Eigen::MatrixXd &amat):mat(amat){}
};

// Create and delete matrices
EigenMatrix* eigen_create(int rows, int cols) {
    return new EigenMatrix(rows, cols);
}

int eigen_rows(const EigenMatrix *A)
{
  return A->mat.rows();
}

int eigen_cols(const EigenMatrix *A)
{
  return A->mat.cols();
}

EigenMatrix* eigen_create_random(int rows, int cols) {
    EigenMatrix* mat = new EigenMatrix(rows, cols);
    mat->mat.setRandom();
    return mat;
}

EigenMatrix* eigen_create_identity(int rows, int cols) {
    EigenMatrix* mat = new EigenMatrix(rows, cols);
    mat->mat.setIdentity();
    return mat;
}

EigenMatrix* eigen_create_ones(int rows, int cols) {
    EigenMatrix* mat = new EigenMatrix(rows, cols);
    mat->mat.setOnes();
    return mat;
}

EigenMatrix* eigen_create_from_array(int rows, int cols, const double* values) {
    EigenMatrix* mat = new EigenMatrix(rows, cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            mat->mat(i, j) = values[i * cols + j];
    return mat;
}

void eigen_copy(EigenMatrix* A, const EigenMatrix* B) {
    // Resize A to match B's dimensions
    A->mat.resize(B->mat.rows(), B->mat.cols());

    // Copy data from B to A
    A->mat = B->mat;
}

EigenMatrix* eigen_duplicate(const EigenMatrix* A) {
    if (!A) {
        std::cerr << "Error: Cannot duplicate a null matrix." << std::endl;
        return nullptr;
    }

    EigenMatrix* duplicate = new EigenMatrix(A->mat.rows(), A->mat.cols());
    duplicate->mat = A->mat; // Copy the matrix contents

    return duplicate;
}


void eigen_free(EigenMatrix* mat) {
    delete mat;
}

// Basic matrix operations
EigenMatrix* eigen_add(const EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.rows() != B->mat.rows() || A->mat.cols() != B->mat.cols())
        return nullptr;
    return new EigenMatrix(A->mat + B->mat);
}

EigenMatrix* eigen_scalar_add(const EigenMatrix* A, double scalar) {
    EigenMatrix* result = new EigenMatrix(A->mat.rows(), A->mat.cols());
    result->mat = A->mat.array() + scalar;
    return result;
}

EigenMatrix* eigen_subtract(const EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.rows() != B->mat.rows() || A->mat.cols() != B->mat.cols())
        return nullptr;
    return new EigenMatrix(A->mat - B->mat);
}

EigenMatrix* eigen_scalar_subtract(const EigenMatrix* A, double scalar) {
    EigenMatrix* result = new EigenMatrix(A->mat.rows(), A->mat.cols());
    result->mat = A->mat.array() - scalar;
    return result;
}


EigenMatrix* eigen_multiply(const EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.cols() != B->mat.rows())
        return nullptr;
    return new EigenMatrix(A->mat * B->mat);
}

EigenMatrix* eigen_scalar_multiply(const EigenMatrix* A, double scalar) {
    EigenMatrix* result = new EigenMatrix(A->mat.rows(), A->mat.cols());
    result->mat = A->mat * scalar;
    return result;
}

EigenMatrix* eigen_scalar_divide(const EigenMatrix* A, double scalar) {
    EigenMatrix* result = new EigenMatrix(A->mat.rows(), A->mat.cols());
    result->mat = A->mat.array() / scalar;
    return result;
}


EigenMatrix* eigen_transpose(const EigenMatrix* A) {
    return new EigenMatrix(A->mat.transpose());
}

EigenMatrix* eigen_inverse(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols())
        return nullptr;
    return new EigenMatrix(A->mat.inverse());
}



// In-place matrix addition: A += B
void eigen_add_inplace(EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.rows() != B->mat.rows() || A->mat.cols() != B->mat.cols()) {
        std::cerr << "Error: Matrix dimensions must match for addition." << std::endl;
        return;
    }
    A->mat += B->mat;
}

// In-place matrix subtraction: A -= B
void eigen_subtract_inplace(EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.rows() != B->mat.rows() || A->mat.cols() != B->mat.cols()) {
        std::cerr << "Error: Matrix dimensions must match for subtraction." << std::endl;
        return;
    }
    A->mat -= B->mat;
}

// In-place matrix multiplication: A = A * B
void eigen_multiply_inplace(EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.cols() != B->mat.rows()) {
        std::cerr << "Error: Incompatible dimensions for matrix multiplication." << std::endl;
        return;
    }
    Eigen::MatrixXd temp = A->mat * B->mat; // Temporary to prevent aliasing
    A->mat = temp;
}

// In-place matrix transpose: A = A^T
void eigen_transpose_inplace(EigenMatrix* A) {
    A->mat.transposeInPlace();
}

// In-place matrix inverse: A = A⁻¹
void eigen_inverse_inplace(EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols()) {
        std::cerr << "Error: Only square matrices can be inverted." << std::endl;
        return;
    }
    A->mat = A->mat.inverse(); // Eigen handles numerical stability
}

// In-place scalar addition: A += scalar
void eigen_scalar_add_inplace(EigenMatrix* A, double scalar) {
    A->mat.array() += scalar; // Element-wise scalar addition
}

// In-place scalar multiplication: A *= scalar
void eigen_scalar_multiply_inplace(EigenMatrix* A, double scalar) {
    A->mat *= scalar;
}

// In-place scalar divide: A /= scalar
void eigen_scalar_divide_inplace(EigenMatrix* A, double scalar) {
    A->mat.array() /= scalar; // Element-wise scalar addition
}

// In-place scalar subtraction: A -= scalar
void eigen_scalar_subtract_inplace(EigenMatrix* A, double scalar) {
  A->mat.array() -= scalar;
}


// Determinant
double eigen_determinant(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols())
        return 0.0;
    return A->mat.determinant();
}

// Access single elements
double eigen_get_element(const EigenMatrix* A, int row, int col) {
    return A->mat(row, col);
}

void eigen_set_element(EigenMatrix* A, int row, int col, double value) {
    A->mat(row, col) = value;
}

// Swap rows and columns
void eigen_swap_rows(EigenMatrix* A, int row1, int row2) {
    A->mat.row(row1).swap(A->mat.row(row2));
}

void eigen_swap_cols(EigenMatrix* A, int col1, int col2) {
    A->mat.col(col1).swap(A->mat.col(col2));
}

// Get single row or column as a new matrix
EigenMatrix* eigen_get_row(const EigenMatrix* A, int row) {
    return new EigenMatrix(A->mat.row(row));
}

EigenMatrix* eigen_get_col(const EigenMatrix* A, int col) {
    return new EigenMatrix(A->mat.col(col));
}

// Get sub-matrix
EigenMatrix* eigen_submatrix(const EigenMatrix* A, int row, int col, int rows, int cols) {
    return new EigenMatrix(A->mat.block(row, col, rows, cols));
}

// Dot product
double eigen_dot(const EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.cols() != 1 || B->mat.cols() != 1 || A->mat.rows() != B->mat.rows())
        return 0.0;
     Eigen::ArrayXXd C = A->mat.array() * B->mat.array();
     return C.sum();
}

// Matrix reductions
double eigen_norm(const EigenMatrix* A) { return A->mat.norm(); }

double eigen_sum(const EigenMatrix* A) { return A->mat.sum(); }
double eigen_product(const EigenMatrix* A) { return A->mat.prod(); }
double eigen_min(const EigenMatrix* A) { return A->mat.minCoeff(); }
double eigen_max(const EigenMatrix* A) { return A->mat.maxCoeff(); }
double eigen_trace(const EigenMatrix* A) { return A->mat.trace(); }

constexpr double DEFAULT_EPSILON = 1e-9; // Default tolerance for floating-point comparisons

// Check if all elements are close to zero
bool eigen_is_zero(const EigenMatrix* A) {
    return (A->mat.array().abs() < DEFAULT_EPSILON).all();
}

// Check if the matrix is an identity matrix
bool eigen_is_identity(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols()) return false; // Must be square
    return (A->mat - Eigen::MatrixXd::Identity(A->mat.rows(), A->mat.cols())).array().abs().maxCoeff() < DEFAULT_EPSILON;
}

// Check if the matrix is square
bool eigen_is_square(const EigenMatrix* A) {
    return A->mat.rows() == A->mat.cols();
}

// Check if the matrix is symmetric (A == A^T)
bool eigen_is_symmetric(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols()) return false; // Must be square
    return (A->mat - A->mat.transpose()).array().abs().maxCoeff() < DEFAULT_EPSILON;
}

// Check if the matrix is diagonal (non-diagonal elements are near zero)
bool eigen_is_diagonal(const EigenMatrix* A) {
    Eigen::MatrixXd off_diag = A->mat;
    off_diag.diagonal().setZero(); // Remove diagonal elements
    return (off_diag.array().abs().maxCoeff() < DEFAULT_EPSILON);
}

// Check if the matrix is orthogonal (A * A^T == I)
bool eigen_is_orthogonal(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols()) return false; // Must be square
    Eigen::MatrixXd identity = A->mat * A->mat.transpose();
    return (identity - Eigen::MatrixXd::Identity(A->mat.rows(), A->mat.cols())).array().abs().maxCoeff() < DEFAULT_EPSILON;
}

// Check if the matrix is singular (determinant is near zero)
bool eigen_is_singular(const EigenMatrix* A) {
    if (A->mat.rows() != A->mat.cols()) return false; // Must be square
    return std::abs(A->mat.determinant()) < DEFAULT_EPSILON;
}

// Check if two matrices are approximately equal
bool eigen_are_equal(const EigenMatrix* A, const EigenMatrix* B) {
    if (A->mat.rows() != B->mat.rows() || A->mat.cols() != B->mat.cols()) return false;
    return (A->mat - B->mat).array().abs().maxCoeff() < DEFAULT_EPSILON;
}

void eigen_print(const EigenMatrix* A) {
    if (!A) {
        std::cerr << "Error: Cannot print a null matrix." << std::endl;
        return;
    }
    std::cout << "Matrix (" << A->mat.rows() << "x" << A->mat.cols() << "):\n" << A->mat << std::endl;
}

void eigen_print_double(double d) {
  std::cout << "double: " << d << std::endl;
}
void eigen_print_int(int i) {
  std::cout << "i32: " << i << std::endl;
}

EigenMatrix* eigen_abs(const EigenMatrix* A) {
    EigenMatrix* result = new EigenMatrix(A->mat.rows(), A->mat.cols());
    result->mat = A->mat.array().abs(); // Apply absolute value element-wise
    return result;
}
