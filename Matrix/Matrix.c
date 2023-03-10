#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../StringExtra/StringExtra.c"
#include "Matrix.h"

#define INITIAL_STR_LENGTH 100
#define MAX_DOUBLE_LENGTH snprintf(NULL, 0, "%lf", __DBL_MAX__)

int matrix_is_square(const Matrix* matrix)
{
    return (!matrix) ? 0 : matrix->x == matrix->y;
}

Matrix* matrix_init(const size_t x, const size_t y)
{
    if(x <= 0 || y <= 0)
        return NULL;

    Matrix* matrix = malloc(sizeof(Matrix*));
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

Matrix* matrix_init_unitary(const size_t x, const size_t y)
{
    if(x != y || x <= 0)
        return NULL;

    Matrix* matrix = matrix_init(x, y);
    if(!matrix)
        return NULL;

    for(size_t x = 0; x < matrix->x; ++x)
        matrix->values[x][x] = 1;

    return matrix;
}

Matrix* matrix_clone(Matrix* destination, const Matrix* source)
{
    if(!source || destination == source)
        return NULL;

    Matrix* new_matrix = matrix_init(source->x, source->y);
    if(!new_matrix)
        return NULL;

    if(!destination)
        destination = new_matrix;
    else
    {
        matrix_destroy(&destination);
        destination = new_matrix;
    }

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            new_matrix->values[x][y] = source->values[x][y];

    return new_matrix;
}

Matrix* matrix_add(const Matrix* matrix1, const Matrix* matrix2)
{
    if(!matrix1 || !matrix2 || matrix1->x != matrix2->x || matrix1->y != matrix2->y)
        return NULL;

    Matrix* new_matrix = matrix_init(matrix1->x, matrix1->y);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            new_matrix->values[x][y] = matrix1->values[x][y] + matrix2->values[x][y];

    return new_matrix;
}

Matrix* matrix_multiply(const Matrix* matrix1, const Matrix* matrix2)
{
    if(!matrix1 || !matrix2 || matrix1->x != matrix2->y)
        return NULL;

    Matrix* new_matrix = matrix_init(matrix1->y, matrix2->x);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            for(size_t mul_pos = 0; mul_pos < new_matrix->x; ++mul_pos)
                new_matrix->values[x][y] += matrix1->values[mul_pos][y] * matrix2->values[x][mul_pos];

    return new_matrix;
}

Matrix* matrix_scalar_multiply(const Matrix* matrix, const double value)
{
    if(!matrix)
        return NULL;

    Matrix* new_matrix = matrix_init(matrix->y, matrix->x);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < new_matrix->y; ++y)
        for(size_t x = 0; x < new_matrix->x; ++x)
            new_matrix->values[y][x] = matrix->values[y][x] * value;

    return new_matrix;
}

Matrix* determinant_reduce(const Matrix* matrix, const size_t x_split, const size_t y_split)
{
    if(!matrix)
        return NULL;

    Matrix* reduced_determinant = matrix_init(matrix->x - 1, matrix->y - 1);
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

double calculate_determinant(const Matrix* matrix)
{
    if(!matrix)
        return 0;

    double** values = matrix->values;
    if(matrix->x == 2)
        return values[0][0] * values[1][1] - values[1][0] * values[0][1];

    double determinant = 0;
    for(size_t x = 0; x < matrix->x; ++x)
    {
        Matrix* reduced_determinant = determinant_reduce(matrix, x, 0);
        if(!reduced_determinant)
            return 0;

        determinant += values[x][0] * pow(-1, x) * calculate_determinant(reduced_determinant);
        matrix_destroy(&reduced_determinant);
    }

    return determinant;
}

double matrix_get_determinant(const Matrix* matrix)
{
    if(!matrix || !matrix_is_square(matrix))
        return 0;

    double** values = matrix->values;
    if(matrix->x == 2)
        return values[0][0] * values[1][1] - values[1][0] * values[0][1];

    if(matrix->x == 1)
        return values[0][0];

    return calculate_determinant(matrix);
}

Matrix* matrix_transpose(const Matrix* matrix)
{
    if(!matrix)
        return NULL;

    Matrix* new_matrix = matrix_init(matrix->y, matrix->x);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < matrix->y; ++y)
        for(size_t x = 0; x < matrix->x; ++x)
            new_matrix->values[y][x] = matrix->values[x][y];

    return new_matrix;
}

Matrix* matrix_inverse(const Matrix* matrix)
{
    if(!matrix)
        return NULL;

    double determinant = matrix_get_determinant(matrix);
    if(determinant == 0)
        return NULL;

    Matrix* new_matrix = matrix_init(matrix->x, matrix->y);
    if(!new_matrix)
        return NULL;

    for(size_t y = 0; y < matrix->y; ++y)
        for(size_t x = 0; x < matrix->x; ++x)
        {
            Matrix* reduced_determinant = determinant_reduce(matrix, x, y);
            if(!reduced_determinant)
                return NULL;

            new_matrix->values[y][x] = matrix_get_determinant(reduced_determinant) * pow(-1, x + y) / determinant;
            matrix_destroy(&reduced_determinant);
        }

    return new_matrix;
}

char* matrix_to_string(const Matrix* matrix)
{
    if(!matrix)
        return NULL;

    size_t capacity = INITIAL_STR_LENGTH;
    size_t length = 0;
    char* string = calloc(capacity + 1, sizeof(char*));
    if(!string)
        return NULL;

    for(size_t y = 0; y < matrix->y; ++y)
    {
        for(size_t x = 0; x < matrix->x; ++x)
        {
            char temp_string[MAX_DOUBLE_LENGTH + 2];
            length += snprintf(temp_string, MAX_DOUBLE_LENGTH + 2, "%.2lf ", matrix->values[y][x]);

            if(length + 1 > capacity) // Account for potential '\n'
            {
                capacity = (capacity << 1) + length;
                char* new_ptr = realloc(string, capacity + 1);
                if(!new_ptr)
                    return string;

                string = new_ptr;
            }
            strlcat(string, temp_string, capacity + 1);
        }
        strlcat(string, "\n\0", capacity + 1);
    }

    return string;
}

void matrix_destroy(Matrix** matrix)
{
    if(!matrix || !(*matrix))
        return;

    for(size_t x = 0; x < (*matrix)->x; ++x)
        free((*matrix)->values[x]);

    free((*matrix)->values);
    free(*matrix);
    *matrix = NULL;
}