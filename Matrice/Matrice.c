#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "Matrice.h"

#define INITIAL_STR_LENGTH 100
#define MAX_DOUBLE_LENGTH 20

int matrice_is_square(const Matrice* matrix)
{
    return (!matrix) ? 0 : matrix->x == matrix->y;
}

Matrice* matrice_init(const size_t x, const size_t y)
{
    if(x <= 0 || y <= 0)
        return NULL;

    Matrice* matrix = malloc(sizeof(Matrice*));
    if(!matrix)
        return NULL;

    matrix->x = x;
    matrix->y = y;

    matrix->values = calloc(x, sizeof(double*));
    if(!matrix->values)
    {
        free(matrix);
        return NULL;
    }

    for(size_t i = 0; i < x; ++i)
    {
        matrix->values[i] = calloc(y, sizeof(double**));
        if(!matrix->values[i])
        {
            free(matrix->values);
            free(matrix);
            return NULL;
        }
    }

    return matrix;
}

Matrice* matrice_init_unitary(const size_t x, const size_t y)
{
    if(x != y || x <= 0)
        return NULL;

    Matrice* matrix = matrice_init(x, y);
    if(!matrix)
        return NULL;

    for(size_t x = 0; x < matrix->x; ++x)
        matrix->values[x][x] = 1;

    return matrix;
}

Matrice* matrice_clone(Matrice** destination, const Matrice* source)
{
    if(!source)
        return NULL;

    Matrice* new_matrix = matrice_init(source->x, source->y);
    if(!new_matrix)
        return NULL;

    if(!destination)
        destination = &new_matrix;
    else
    {
        matrice_destroy(destination);
        *destination = new_matrix;
    }

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            new_matrix->values[x][y] = source->values[x][y];

    return new_matrix;
}

Matrice* matrice_add(const Matrice* matrix1, const Matrice* matrix2)
{
    if(!matrix1 || !matrix2 || matrix1->x != matrix2->x || matrix1->y != matrix2->y)
        return NULL;

    Matrice* new_matrix = matrice_init(matrix1->x, matrix1->y);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            new_matrix->values[x][y] = matrix1->values[x][y] + matrix2->values[x][y];

    return new_matrix;
}

Matrice* matrice_multiply(const Matrice* matrix1, const Matrice* matrix2)
{
    if(!matrix1 || !matrix2 || matrix1->x != matrix2->y)
        return NULL;

    Matrice* new_matrix = matrice_init(matrix1->y, matrix2->x);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            for(size_t mul_pos = 0; mul_pos < new_matrix->x; ++mul_pos)
                new_matrix->values[x][y] += matrix1->values[mul_pos][y] * matrix2->values[x][mul_pos];

    return new_matrix;
}

Matrice* determinant_reduce(const Matrice* matrix, const size_t x_split, const size_t y_split)
{
    if(!matrix || x_split < 0 || y_split < 0)
        return NULL;

    Matrice* reduced_determinant = matrice_init(matrix->x - 1, matrix->y - 1);
    if(!reduced_determinant)
        return NULL;

    size_t current_y = 0;
    for(size_t y = 0; y < matrix->y; ++y)
    {
        if(y == y_split)
            continue;

        size_t current_x = 0;
        for(size_t x = 0; x < matrix->x; ++x)
        {
            if(x == x_split)
                continue;

            reduced_determinant->values[current_x][current_y] = matrix->values[x][y];
            ++current_x;
        }
        ++current_y;
    }

    return reduced_determinant;
}

double calculate_determinant(const Matrice* matrix)
{
    if(!matrix)
        return 0;

    double** values = matrix->values;
    if(matrix->x == 2)
        return values[0][0] * values[1][1] - values[1][0] * values[0][1];

    double determinant = 0;
    for(size_t x = 0; x < matrix->x; ++x)
    {
        Matrice* reduced_determinant = determinant_reduce(matrix, x, 0);
        if(!reduced_determinant)
            return 0;

        determinant += values[x][0] * pow(-1, x) * calculate_determinant(reduced_determinant);
        matrice_destroy(&reduced_determinant);
    }

    return determinant;
}

double matrice_get_determinant(const Matrice* matrix)
{
    if(!matrix || !matrice_is_square(matrix))
        return 0;

    double** values = matrix->values;
    if(matrix->x == 2)
        return values[0][0] * values[1][1] - values[1][0] * values[0][1];

    if(matrix->x == 1)
        return values[0][0];

    return calculate_determinant(matrix);
}

Matrice* matrice_transpose(const Matrice* matrix)
{
    if(!matrix)
        return NULL;

    Matrice* new_matrix = matrice_init(matrix->y, matrix->x);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < matrix->y; ++y)
        for(size_t x = 0; x < matrix->x; ++x)
            new_matrix->values[y][x] = matrix->values[x][y];

    return new_matrix;
}

Matrice* matrice_inverse(const Matrice* matrix)
{
    if(!matrix)
        return NULL;

    double determinant = matrice_get_determinant(matrix);
    if(determinant == 0)
        return NULL;

    Matrice* new_matrix = matrice_init(matrix->x, matrix->y);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < matrix->y; ++y)
        for(size_t x = 0; x < matrix->x; ++x)
        {
            Matrice* reduced_determinant = determinant_reduce(matrix, x, y);
            if(!reduced_determinant)
                return NULL;

            new_matrix->values[y][x] = matrice_get_determinant(reduced_determinant) * pow(-1, x + y) / determinant;
            matrice_destroy(&reduced_determinant);
        }

    return new_matrix;
}

char* matrice_to_string(const Matrice* matrix)
{
    char* string = calloc(INITIAL_STR_LENGTH, sizeof(char*));
    size_t buffer_capacity = INITIAL_STR_LENGTH;
    size_t length = 0;

    for(size_t y = 0; y < matrix->y; ++y)
    {
        for(size_t x = 0; x < matrix->x; ++x)
        {
            char temp_string[MAX_DOUBLE_LENGTH + 1];
            length += snprintf(temp_string, MAX_DOUBLE_LENGTH, "%.2f ", matrix->values[y][x]);

            if(length > buffer_capacity - 1)
            {
                buffer_capacity = buffer_capacity * 2 + length;
                char* new_ptr = realloc(string, buffer_capacity);
                if(!new_ptr)
                    return string;

                string = new_ptr;
            }
            strncat(string, temp_string, buffer_capacity - 1);
        }
        strncat(string, "\n\0", buffer_capacity - 1);
    }

    return string;
}

void matrice_destroy(Matrice** matrix)
{
    if(!matrix || !(*matrix))
        return;

    for(size_t x = 0; x < (*matrix)->x; ++x)
        free((*matrix)->values[x]);

    free((*matrix)->values);
    free(*matrix);
    *matrix = NULL;
}