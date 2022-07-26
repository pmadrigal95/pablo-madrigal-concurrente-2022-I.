// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_MATRIX_UTILITY_H_
#define SRC_MATRIX_UTILITY_H_

#include <stddef.h>

/**
 * @brief Crear una matriz
 * @details Retorna una nueva matrix
 * @param size_t row_count
 * @param size_t col_count
 * @param size_t element_size
 * @return void **create_matrix
 *
 */
void **create_matrix(size_t row_count, size_t col_count, size_t element_size);

/**
 * @brief Liberar memoria de una matriz
 * @details Liberar memoria de una matriz
 * @param size_t row_count
 * @param void **matrix
 *
 */
void free_matrix(const size_t row_count, void **matrix);

/**
 * @details Clona tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return Clona tablero de juego en el destino
 *
 */
char **clone_char_matrix(char **origin, char **destiny,
                        size_t row_count, size_t col_count);

/**
 * @details Crea un nuevo tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return nuevo tablero de juego
 *
 */
char** generate_matrix_from_another(char** origin,
    size_t row_count, size_t col_count);

/**
 * @brief Crear un vector
 * @details Retorna un nuevo vector
 * @param size_t row_count
 * @param size_t element_size
 * @return void **create_array
 *
 */
void *create_array(size_t row_count, size_t element_size);

/**
 * @brief Liberar memoria de un vector
 * @details Liberar memoria de un vector
 * @param void *array
 *
 */
void free_array(void *array);

/**
 * @brief Imprimir por pantalla una matriz
 * @details Imprimir por pantalla una matriz
 * @param size_t row_count
 * @param size_t col_count
 *
 */
void print_char_matrix(char ** matrix, size_t row_count, size_t col_count);

#endif  // SRC_MATRIX_UTILITY_H_
