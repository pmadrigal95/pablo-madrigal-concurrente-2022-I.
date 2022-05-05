// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stddef.h>
#include <stdlib.h>

void free_matrix(const size_t row_count, void **matrix);

void **create_matrix(size_t row_count, size_t col_count, size_t element_size) {
    void **matrix =
        (void **)calloc(row_count, sizeof(void *));

    if (matrix == NULL) {
        return NULL;
    }

    for (size_t row = 0; row < row_count; ++row) {
        if ((matrix[row] = calloc(col_count, element_size)) == NULL) {
            return free_matrix(row_count, matrix), NULL;
        }
    }

    return matrix;
}

void free_matrix(const size_t row_count, void **matrix) {
    if (matrix) {
        for (size_t row = 0; row < row_count; ++row)
            free(matrix[row]);
    }

    free(matrix);
}

void *create_array(size_t row_count, size_t element_size) {
    void *array =
        (void *)calloc(row_count, element_size);

    if (array == NULL) {
        return NULL;
    }

    return array;
}

void free_array(void *array) {
    free(array);
}
