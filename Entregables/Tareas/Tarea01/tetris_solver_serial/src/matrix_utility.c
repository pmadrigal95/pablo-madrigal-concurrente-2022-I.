// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

void free_matrix(const size_t row_count, void **matrix);

/*
* Public Methods
*/

/**
 * @brief Crear una matriz
 * @details Retorna una nueva matrix
 * @param size_t row_count
 * @param size_t col_count
 * @param size_t element_size
 * @return void **create_matrix
 *
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

/**
 * @brief Liberar memoria de una matriz
 * @details Liberar memoria de una matriz
 * @param size_t row_count
 * @param void **matrix
 *
 */
void free_matrix(const size_t row_count, void **matrix) {
    if (matrix) {
        for (size_t row = 0; row < row_count; ++row)
            free(matrix[row]);
    }

    free(matrix);
}

/**
 * @details Clona tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return Clona tablero de juego en el destino
 *
 */
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

/**
 * @details Crea un nuevo tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return nuevo tablero de juego
 *
 */
char** generate_matrix_from_another(char** origin,
    size_t row_count, size_t col_count) {
    char **destiny = (char **)
        create_matrix((row_count + 1),
            (col_count + 1), sizeof(char));

    destiny = clone_char_matrix(origin, destiny, row_count, col_count);

    return destiny;
}

/**
 * @brief Crear un vector
 * @details Retorna un nuevo vector
 * @param size_t row_count
 * @param size_t element_size
 * @return void **create_array
 *
 */
void *create_array(size_t row_count, size_t element_size) {
    void *array =
        (void *)calloc(row_count, element_size);

    if (array == NULL) {
        return NULL;
    }

    return array;
}

/**
 * @brief Liberar memoria de un vector
 * @details Liberar memoria de un vector
 * @param void *array
 *
 */
void free_array(void *array) {
    free(array);
}

/**
 * @brief Imprimir por pantalla una matriz
 * @details Imprimir por pantalla una matriz
 * @param size_t row_count
 * @param size_t col_count
 *
 */
void print_char_matrix(char ** matrix, size_t row_count, size_t col_count) {
    for (size_t x = 0; x < row_count; x++) {
            for (size_t i = 0; i < col_count; i++) {
                printf("%c", matrix[x][i]);
            }
            printf("\n");
        }
}
