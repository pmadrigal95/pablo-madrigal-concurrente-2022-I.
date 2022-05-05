// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_FILE_UTILITY_H_
#define SRC_FILE_UTILITY_H_

#include "structures.h"

/**
 * @brief Get a input_data_t ptr to start the program
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param file path
 * @param input_data Struct
 * @return If file is not valid, it returns Error
 *
 */
void get_input_data(char *filename, input_data_t* input_data);

#endif  // SRC_FILE_UTILITY_H_
