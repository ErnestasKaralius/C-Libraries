# Matrice Documentation

| Function                                                                   | Description                                                            |
|----------------------------------------------------------------------------|-----------------------------------------------------------------------|
| Matrice* matrice_init(const size_t x, const size_t y);                     | Returns a pointer to a Matrix of specified size filled with 0's, otherwise NULL |
| Matrice* matrice_init_unitary(const size_t x, const size_t y);             | Returns a pointer to a Unitary Matrix of specified size, otherwise NULL |
| Matrice* matrice_clone(Matrice** destination, const Matrice* source);      | Clones the source Matrix to destination. Returns a pointer to the cloned Matrix, otherwise NULL. Destination can be NULL |
| Matrice* matrice_add(const Matrice* matrix1, const Matrice* matrix2);      | Adds two Matrices together. Returns a pointer to the new Matrix, otherwise NULL |
| Matrice* matrice_multiply(const Matrice* matrix1, const Matrice* matrix2); | Multiplies two Matrices together. Returns a pointer to the new Matrix, otherwise NULL |
|Matrice* matrice_scalar_multiply(const Matrice* matrix, const double value);| Multiplies a Matrix by a value. Returns a pointer to a new Matrix, otherwise NULL |
|Matrice* matrice_transpose(const Matrice* matrix);                          | Transposes a Matrix. Returns a pointer to the transposed Matrix, otherwise NULL
| Matrice* matrice_inverse(const Matrice* matrix);                           | Inverses a Matrix. Returns a pointer to the inversed Matrix, otherwise NULL |
| int matrice_is_square(const Matrice* matrix);                              | Returns 1 if the x and y sizes of a Matrix are equal, otherwise 0 |
| double matrice_get_determinant(const Matrice* matrix);                     | Returns the Determinant of a Matrix |
| char* matrice_to_string(const Matrice* matrix);                            | Converts the values of a Matrix to a string. Returns a pointer to the start of the string, otherwise NULL |
| void matrice_destroy(Matrice** matrix);                                    | Frees the Matrix from memory |
