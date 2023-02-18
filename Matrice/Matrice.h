#ifndef MATRICES_H_INCLUDED
#define MATRICES_H_INCLUDED

#include <stdio.h>

typedef struct Matrice {
    size_t x, y;
    double** values;
} Matrice;

Matrice* matrice_init(const size_t x, const size_t y);
Matrice* matrice_init_unitary(const size_t x, const size_t y);
Matrice* matrice_clone(Matrice** destination, const Matrice* source);

Matrice* matrice_add(const Matrice* matrix1, const Matrice* matrix2);
Matrice* matrice_multiply(const Matrice* matrix1, const Matrice* matrix2);
Matrice* matrice_transpose(const Matrice* matrix);
Matrice* matrice_inverse(const Matrice* matrix);

double matrice_get_determinant(const Matrice* matrix);
char* matrice_to_string(const Matrice* matrix);
int matrice_is_square(const Matrice* matrix);

void matrice_destroy(Matrice** matrix);


#endif // MATRICES_H_INCLUDED
