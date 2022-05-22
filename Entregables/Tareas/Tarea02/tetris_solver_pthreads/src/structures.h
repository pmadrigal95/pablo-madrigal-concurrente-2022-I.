// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_STRUCTURES_H_
#define SRC_STRUCTURES_H_

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
    char figure[1];
    size_t rotation;
    size_t rows;
    size_t columns;
    char **table;
    size_t figure_count;
} output_data_t;


typedef struct private_data {
    input_data_t *input_data;
    output_data_t *output_data;
    char **current_status;
    int num_rotations;
    size_t current_profundity;
    size_t thread_num;
    size_t num_threads;
} private_data_t;
#endif  // SRC_STRUCTURES_H_
