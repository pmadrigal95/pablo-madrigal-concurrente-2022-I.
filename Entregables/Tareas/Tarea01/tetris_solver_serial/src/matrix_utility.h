// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_MATRIX_UTILITY_H_
#define SRC_MATRIX_UTILITY_H_

#include <stddef.h>

/**
 * @brief Get a input_data_t ptr to start the program
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param file path
 * @param input_data Struct
 * @return If file is not valid, it returns Error
 *
 */
void **create_matrix(size_t row_count, size_t col_count, size_t element_size);

void free_matrix(const size_t row_count, void **matrix);

char **clone_char_matrix(char **origin, char **destiny,
                        size_t row_count, size_t col_count);

char** generate_matrix_from_another(char** origin,
    size_t row_count, size_t col_count);

void *create_array(size_t row_count, size_t element_size);

void free_array(void *array);

#endif  // SRC_MATRIX_UTILITY_H_
