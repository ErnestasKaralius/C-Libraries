# Matrice Documentation

| Function                                                                   | Description                                                            |
|----------------------------------------------------------------------------|-----------------------------------------------------------------------|
| Matrice* matrice_init(const size_t x, const size_t y);                     | Returns a pointer to a Matrix of specified size, otherwise NULL |
| Matrice* matrice_init_unitary(const size_t x, const size_t y);             | Returns a pointer to a Unitary Matrix of specified size, otherwise NULL |
| Matrice* matrice_clone(Matrice** destination, const Matrice* source);      | 
| Matrice* matrice_add(const Matrice* matrix1, const Matrice* matrix2);      |
| Matrice* matrice_multiply(const Matrice* matrix1, const Matrice* matrix2); |
| Matrice* matrice_transpose(const Matrice* matrix);                         |
| Matrice* matrice_inverse(const Matrice* matrix);                           |
| int matrice_is_square(const Matrice* matrix);                              |
| double matrice_get_determinant(const Matrice* matrix);                     |
| char* matrice_to_string(const Matrice* matrix);                            |
| void matrice_destroy(Matrice** matrix);                                    |
