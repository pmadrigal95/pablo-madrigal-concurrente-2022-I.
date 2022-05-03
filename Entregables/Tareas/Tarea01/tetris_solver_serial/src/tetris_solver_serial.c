// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "./utilities/data/structures.h"
#include "./utilities/file_utility.h"
#include "./utilities/game_logic.h"

void get_input_data(char *filename, input_data_t *input_data);
void next_play(input_data_t* input_data);

int main(int argc, char **arg) {
    char *filename = "../test/test01.txt";
    if (argc == 2) {
        filename = arg[1];
    }

    printf("Inicio del Programa [tetris_solver_serial]\n");

    input_data_t *input_data = (input_data_t *)calloc(1,
                                                      sizeof(input_data_t));

    get_input_data(filename, input_data);

    next_play(input_data);
}
