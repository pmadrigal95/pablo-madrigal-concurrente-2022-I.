// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_FILE_UTILITIES_H_
#define ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_FILE_UTILITIES_H_

#include "./data/structures.h"

/**
 * @brief Get a input_data_t ptr to start the program
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param file path
 * @param input_data Struct
 * @return If file is not valid, it returns Error
 *
 */
void get_input_data(char *filename, input_data_t* input_data);

#endif  // ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_LOGIC_FILE_UTILITIES_H_
