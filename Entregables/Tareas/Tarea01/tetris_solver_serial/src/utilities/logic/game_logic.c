// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include "game_logic.h"
#include "tetris_figure_factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int get_tetris_figure_num_rotations(char figure);
figure_t *get_tetris_figure(char figure, int num_rotations);


void next_play(input_data_t *input_data) {
    printf("Inicio de calculo de la partida [%zu]", input_data->identifier);
    printf(",Profundidad [%zu],", input_data->profundity);
    printf(" Tablero [%zu][%zu]\n", input_data->rows, input_data->columns);


    printf("Estado del Tablero\n");

    for (size_t x = 0; x < input_data->rows; x++) {
        for (size_t i = 0; i < input_data->columns; i++) {
            printf("%c", input_data->table[x][i]);
        }
        printf("\n");
    }

    for (size_t prof = 0; prof <= input_data->profundity; prof++) {
        printf("\nSiguiente Figura [%c]\n", input_data->next_figures[prof]);

        int num_rotations =
            get_tetris_figure_num_rotations(input_data->next_figures[prof]);

        printf("Rotaciones de la Figura [%c] : [%d]\n\n",
               input_data->next_figures[prof], num_rotations);

        char temp[input_data->rows][input_data->columns];

        for (size_t x = 0; x < input_data->rows; x++) {
            for (size_t i = 0; i < input_data->columns; i++) {
                sscanf(&input_data->table[x][i], "%c",
                &temp[input_data->rows - x - 1][input_data->columns - i - 1]);
            }
        }

        figure_t *figure =
                get_tetris_figure(input_data->next_figures[prof], 1);

            printf("Altura [%d], Ancho [%d]\n",
               figure->height, figure->width);


        for (size_t i = 0; i < input_data->rows; i++) {
            bool terminar = false;
            printf("Fila -> %zu\n", i);
            for (size_t j = 0; j < input_data->columns; j++) {
                if (i + figure->height > input_data->rows) {
                    printf("No cabe la pieza a lo alto\n");
                    return;
                }

                printf("Columna -> %zu\n", j);

                if (j + figure->width > input_data->columns) {
                    break;
                }

                int sum = 0;

                for (int k = 0; k < figure->height; k++) {
                    for (int l = 0; l < figure->width; l++) {
                        if (figure->value[k][l] != '0') {
                            sum = temp[i+k][j+l] - '0' + sum;
                        }
                    }
                }

                printf("%d\n", sum);
                if (sum > 0) {
                    continue;
                }

                for (int m = 0; m < figure->height ; m++) {
                    for (int n = 0; n < figure->width; n++) {
                        if (figure->value[m][n] != '0') {
                            sscanf(&figure->value[m][n], "%c", &temp[i+m][j+n]);
                        }
                    }
                }

            terminar = true;
            break;
            }
            if (terminar) {
             break;
            }
        }

        for (size_t x = 0; x < input_data->rows; x++) {
            for (size_t i = 0; i < input_data->columns; i++) {
                printf("%c", temp[input_data->rows - x - 1]
                            [input_data->columns - i - 1]);
            }
            printf("\n");
        }

        /*for (int rot = 0; rot < num_rotations; rot++) {
            figure_t *figure =
                get_tetris_figure(input_data->next_figures[prof], rot);

            printf("Altura [%d], Ancho [%d]\n",
               figure->height, figure->width);

            for (int x = 0; x < figure->height; x++) {
                for (int i = 0; i < figure->width; i++) {
                    printf("%c", figure->value[x][i]);
                }
                printf("\n");
            }
        }*/
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