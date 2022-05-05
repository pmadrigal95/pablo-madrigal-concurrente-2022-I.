// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void free_matrix(const size_t row_count, void **matrix);

/*
* Public Methods
*/

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

char **clone_char_matrix(char **origin, char **destiny,
                        size_t row_count, size_t col_count) {
    for (size_t x = 0; x < row_count; x++) {
        for (size_t i = 0; i < col_count; i++) {
            sscanf(&origin[x][i], "%c",
                   &destiny[x][i]);
        }
    }
    return destiny;
}

char** generate_matrix_from_another(char** origin,
    size_t row_count, size_t col_count) {
    char **destiny = (char **)
        create_matrix((row_count + 1),
            (col_count + 1), sizeof(char));

    destiny = clone_char_matrix(origin, destiny, row_count, col_count);

    return destiny;
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
