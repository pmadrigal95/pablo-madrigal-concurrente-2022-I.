// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "./utilities/data/structures.h"
#include "./utilities/logic/file_utilities.h"

void get_input_data(char *filename, input_data_t *input_data);

int main(int argc, char **arg)
{
    char *filename = "../test/test01.txt";
    if (argc == 2)
    {
        filename = arg[1];
    }

    input_data_t *input_data = (input_data_t *)calloc(1,
                                                      sizeof(input_data_t));

    get_input_data(filename, input_data);

    printf("%zu\n", input_data->identifier);
    printf("%zu\n", input_data->profundity);

    /* visualizamos la matriz*/
    for (size_t x = 0; x < input_data->rows; x++)
    {
        for (size_t i = 0; i < input_data->columns; i++) {
            printf("%c", input_data->matriz[x][i]);
        }
        printf("\n");
    }

    printf("%zu\n", input_data->number_of_figures);

    for (size_t j = 0; j < input_data->number_of_figures; j++) {
        printf("%c\n", input_data->next_figures[j]);
    }

    free(input_data->matriz);

    free(input_data);
}
