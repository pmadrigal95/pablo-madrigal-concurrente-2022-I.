// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_DATA_STRUCTURES_H_
#define ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_DATA_STRUCTURES_H_

#include <stddef.h>

typedef struct input_data {
    size_t identifier;
    size_t profundity;
    size_t rows;
    size_t columns;
    char **table;
    size_t number_of_figures;
    char *next_figures;
} input_data_t;

typedef struct output_data {
    size_t identifier;
    size_t figure;
    size_t rotation;
    size_t rows;
    size_t columns;
    char **table;
} output_data_t;

#endif  // ENTREGABLES_TAREAS_TAREA01_TETRIS_SOLVER_SERIAL_SRC_UTILITIES_DATA_STRUCTURES_H_
