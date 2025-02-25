#ifndef EIGEN_C_H
#define EIGEN_C_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct EigenMatrix EigenMatrix;

// Create and delete matrices
EigenMatrix* eigen_create(int rows, int cols);
EigenMatrix* eigen_create_ones(int rows, int cols);
EigenMatrix* eigen_create_random(int rows, int cols);
EigenMatrix* eigen_create_identity(int rows, int cols);
EigenMatrix* eigen_create_from_array(int rows, int cols, const double* values);
void eigen_free(EigenMatrix* mat);

// Copy the contents of one matrix into an existing matrix
void eigen_copy(EigenMatrix* dest, const EigenMatrix* src);
// Duplicate a matrix (returns a new matrix with the same values as A)
EigenMatrix* eigen_duplicate(const EigenMatrix* A);

  
// Basic matrix operations
EigenMatrix* eigen_add(const EigenMatrix* A, const EigenMatrix* B);
EigenMatrix* eigen_subtract(const EigenMatrix* A, const EigenMatrix* B);
EigenMatrix* eigen_multiply(const EigenMatrix* A, const EigenMatrix* B);
EigenMatrix* eigen_transpose(const EigenMatrix* A);
EigenMatrix* eigen_inverse(const EigenMatrix* A);


EigenMatrix* eigen_scalar_add(const EigenMatrix* A, double scalar);
EigenMatrix* eigen_scalar_subtract(const EigenMatrix* A, double scalar);
EigenMatrix* eigen_scalar_multiply(const EigenMatrix* A, double scalar);
EigenMatrix* eigen_scalar_divide(const EigenMatrix* A, double scalar);


// In-place matrix operations (A is updated)
void eigen_add_inplace(EigenMatrix* A, const EigenMatrix* B);
void eigen_subtract_inplace(EigenMatrix* A, const EigenMatrix* B);
void eigen_multiply_inplace(EigenMatrix* A, const EigenMatrix* B);
void eigen_transpose_inplace(EigenMatrix* A);
void eigen_inverse_inplace(EigenMatrix* A);

// In-place scalar operations (A is updated)
void eigen_scalar_add_inplace(EigenMatrix* A, double scalar);
void eigen_scalar_multiply_inplace(EigenMatrix* A, double scalar);
void eigen_scalar_divide_inplace(EigenMatrix* A, double scalar);
void eigen_scalar_subtract_inplace(EigenMatrix* A, double scalar);
  
// Return number of rows or columns
int eigen_rows(const EigenMatrix *A);
int eigen_cols(const EigenMatrix *A);
  
// Determinant
double eigen_determinant(const EigenMatrix* A);

// Access single elements
double eigen_get_element(const EigenMatrix* A, int row, int col);
void eigen_set_element(EigenMatrix* A, int row, int col, double value);

// Swap rows and columns
void eigen_swap_rows(EigenMatrix* A, int row1, int row2);
void eigen_swap_cols(EigenMatrix* A, int col1, int col2);

// Get single row or column as a new matrix
EigenMatrix* eigen_get_row(const EigenMatrix* A, int row);
EigenMatrix* eigen_get_col(const EigenMatrix* A, int col);

// Get sub-matrix (block)
EigenMatrix* eigen_submatrix(const EigenMatrix* A, int row, int col, int rows, int cols);

// Dot product (only works for 1-column matrices)
double eigen_dot(const EigenMatrix* A, const EigenMatrix* B);


// Matrix reductions
double eigen_sum(const EigenMatrix* A);
double eigen_product(const EigenMatrix* A);
double eigen_min(const EigenMatrix* A);
double eigen_max(const EigenMatrix* A);
double eigen_trace(const EigenMatrix* A);
double eigen_norm(const EigenMatrix* A);

bool eigen_is_zero(const EigenMatrix* A);
bool eigen_is_identity(const EigenMatrix* A);
bool eigen_is_square(const EigenMatrix* A);
bool eigen_is_symmetric(const EigenMatrix* A);
bool eigen_is_diagonal(const EigenMatrix* A);
bool eigen_is_orthogonal(const EigenMatrix* A);
bool eigen_is_singular(const EigenMatrix* A);
bool eigen_are_equal(const EigenMatrix* A, const EigenMatrix* B);

// Print a matrix to the console
void eigen_print(const EigenMatrix* A);
void eigen_print_double(double);
void eigen_print_int(int);

// Compute the element-wise absolute value of a matrix
EigenMatrix* eigen_abs(const EigenMatrix* A);

  
#ifdef __cplusplus
}
#endif

#endif // EIGEN_C_H
