// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_GAME_LOGIC_UTILITY_H_
#define SRC_GAME_LOGIC_UTILITY_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_utility.h"
#include "matrix_utility.h"
#include "tetris_figure_factory.h"

void initial_status(input_data_t *input_data,
                    output_data_t *output_data);

void create_output_data(input_data_t *input_data,
                    output_data_t *output_data);

char** set_game_state(char** origin, size_t row_count,
                        size_t col_count);

void calculate_next_figure(input_data_t *input_data,
                            output_data_t *output_data);

char** clone_game_state(char** origin, char **destiny,
                        size_t row_count, size_t col_count);

size_t get_play_score(char** table, size_t row_count, size_t col_count);

void update_game_board(output_data_t *output_data, char** table);

void generate_game_board_txt(output_data_t *output_data,
                            size_t profundity, char figure);

void validate_insert(figure_t *figure, char **current_status,
                        output_data_t *output_data);

int review_space(figure_t *figure, char **temp,
                size_t row_count, size_t col_count);

#endif  // SRC_GAME_LOGIC_UTILITY_H_
