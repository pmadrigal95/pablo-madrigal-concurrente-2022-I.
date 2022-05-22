// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_GAME_LOGIC_H_
#define SRC_GAME_LOGIC_H_

#include "structures.h"

/**
 * @brief Compute next move from input_data_t ptr
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param input_data_t ptr 
 * @return Best possible move
 *
 */
void next_play(input_data_t *input_data, size_t thread_count);

#endif  // SRC_GAME_LOGIC_H_
