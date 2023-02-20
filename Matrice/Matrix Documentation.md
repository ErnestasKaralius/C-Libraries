# Matrix Documentation

| Function                                                                   | Description                                                            |
|----------------------------------------------------------------------------|-----------------------------------------------------------------------|
| Matrix* matrix_init(const size_t x, const size_t y);                     | Returns a pointer to a Matrix of specified size filled with 0's, otherwise NULL |
| Matrix* matrix_init_unitary(const size_t x, const size_t y);             | Returns a pointer to a Unitary Matrix of specified size, otherwise NULL |
| Matrix* matrix_clone(Matrix** destination, const Matrix* source);      | Clones the source Matrix to destination. Returns a pointer to the cloned Matrix, otherwise NULL. Destination can be NULL |
| Matrix* matrix_add(const Matrix* matrix1, const Matrix* matrix2);      | Adds two Matrices together. Returns a pointer to the new Matrix, otherwise NULL |
| Matrix* matrix_multiply(const Matrix* matrix1, const Matrix* matrix2); | Multiplies two Matrices together. Returns a pointer to the new Matrix, otherwise NULL |
|Matrix* matrix_scalar_multiply(const Matrix* matrix, const double value);| Multiplies a Matrix by a value. Returns a pointer to a new Matrix, otherwise NULL |
|Matrix* matrix_transpose(const Matrix* matrix);                          | Transposes a Matrix. Returns a pointer to the transposed Matrix, otherwise NULL
| Matrix* matrix_inverse(const Matrix* matrix);                           | Inverses a Matrix. Returns a pointer to the inversed Matrix, otherwise NULL |
| int matrix_is_square(const Matrix* matrix);                              | Returns 1 if the x and y sizes of a Matrix are equal, otherwise 0 |
| double matrix_get_determinant(const Matrix* matrix);                     | Returns the Determinant of a Matrix |
| char* matrix_to_string(const Matrix* matrix);                            | Converts the values of a Matrix to a string. Returns a pointer to the start of the string, otherwise NULL |
| void matrix_destroy(Matrix** matrix);                                    | Frees the Matrix from memory |
