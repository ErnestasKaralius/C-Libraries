#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#define size_t unsigned long

typedef struct Matrix {
    size_t x, y;
    double** values;
} Matrix;

Matrix* matrix_init(const size_t x, const size_t y);
Matrix* matrix_init_unitary(const size_t x, const size_t y);
Matrix* matrix_clone(Matrix* destination, const Matrix* source);

Matrix* matrix_add(const Matrix* matrix1, const Matrix* matrix2);
Matrix* matrix_multiply(const Matrix* matrix1, const Matrix* matrix2);
Matrix* matrix_scalar_multiply(const Matrix* matrix, const double value);
Matrix* matrix_transpose(const Matrix* matrix);
Matrix* matrix_inverse(const Matrix* matrix);

double matrix_get_determinant(const Matrix* matrix);
char* matrix_to_string(const Matrix* matrix);
int matrix_is_square(const Matrix* matrix);

void matrix_destroy(Matrix** matrix);


#endif // MATRICES_H_INCLUDED
