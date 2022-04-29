// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_GAME_LOGIC_H_
#define ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_GAME_LOGIC_H_

#include "../data/structures.h"

/**
 * @brief Compute next move from input_data_t ptr
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param input_data_t ptr 
 * @return Best possible move
 *
 */
void next_play(input_data_t* input_data);

#endif  // ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_GAME_LOGIC_H_ _
