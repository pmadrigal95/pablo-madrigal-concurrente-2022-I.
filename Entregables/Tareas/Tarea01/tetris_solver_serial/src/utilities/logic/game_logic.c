// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include "game_logic.h"
#include "tetris_figure_factory.h"
#include <stdio.h>
#include <stdlib.h>

int get_tetris_figure_num_rotations(char figure);
figure_t* get_tetris_figure(char figure, int num_rotations);


void next_play(input_data_t *input_data) {
    printf("Inicio de calculo de la partida [%zu]", input_data->identifier);
    printf(",Profundidad [%zu],", input_data->profundity);
    printf(" Tablero [%zu][%zu]\n", input_data->rows, input_data->columns);

    for (size_t prof = 0; prof <= input_data->profundity; prof++) {
        printf("Siguiente Figura [%c]\n", input_data->next_figures[prof]);

        int num_rotations =
            get_tetris_figure_num_rotations(input_data->next_figures[prof]);

        printf("Rotaciones de la Figura [%c] : [%d]\n",
        input_data->next_figures[prof], num_rotations);

        /*figure_t *figure = (figure_t *)malloc(1 * sizeof(figure_t));

        figure =
            get_tetris_figure(input_data->next_figures[prof], num_rotations);

        printf("height [%d], width [%d]\n",
        figure->height, figure->width);

        free(figure);*/
    }

    /*printf("%zu\n", input_data->identifier);
    printf("%zu\n", input_data->profundity);

    for (size_t x = 0; x < input_data->rows; x++)
    {
        for (size_t i = 0; i < input_data->columns; i++)
        {
            printf("%c", input_data->table[x][i]);
        }
        printf("\n");
    }

    printf("%zu\n", input_data->number_of_figures);

    for (size_t j = 0; j < input_data->number_of_figures; j++)
    {
        printf("%c\n", input_data->next_figures[j]);
    }*/
}
