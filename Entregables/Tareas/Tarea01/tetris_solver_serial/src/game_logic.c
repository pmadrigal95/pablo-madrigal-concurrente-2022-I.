// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "game_logic.h"
#include "file_utility.h"
#include "matrix_utility.h"
#include "tetris_figure_factory.h"

/**
* Imports Utilities
*/

/*
* tetris_figure_factory.h
*/

int get_tetris_figure_num_rotations(char figure);

figure_t *get_tetris_figure(char figure, int num_rotations);

/*
* matrix_utility.h
*/

char **clone_char_matrix(char **origin, char **destiny,
                        size_t row_count, size_t col_count);

char** generate_matrix_from_another(char** origin,
                        size_t row_count, size_t col_count);

void free_array(void *array);

void print_char_matrix(char ** matrix, size_t row_count, size_t col_count);

/*
* file_utility.h
*/

void generate_output_file(size_t profundity, output_data_t *output_data);

/*
* Private 
*/

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


/*
* Public Methods
*/
void next_play(input_data_t *input_data) {
    output_data_t *output_data = (output_data_t *)calloc(1,
                                                sizeof(output_data_t));
    initial_status(input_data, output_data);

    calculate_next_figure(input_data, output_data);

    free_matrix(input_data->rows, (void **)input_data->table);
    free(input_data);

    free_array((void **)input_data->next_figures);
    free_matrix(output_data->rows, (void **)output_data->table);
    free(output_data);
}


/*
* Private Methods
*/
void initial_status(input_data_t *input_data, output_data_t *output_data) {
    /**     
     * Crear  Objeto de Salida
     */
    create_output_data(input_data, output_data);

    /**     
     * Estado Inicial
     */
    printf("Inicio de calculo de la partida [%zu]", input_data->identifier);
    printf(",Profundidad [%zu],", input_data->profundity);
    printf(" Tablero [%zu][%zu]\n", input_data->rows, input_data->columns);

    printf("Estado del Tablero\n");

    print_char_matrix(input_data->table, input_data->rows,
            input_data->columns);
}

void create_output_data(input_data_t *input_data, output_data_t *output_data) {
    output_data->identifier = input_data->identifier;
    output_data->rows = input_data->rows;
    output_data->columns = input_data->columns;

     output_data->table =
        set_game_state(input_data->table, input_data->rows,
                        input_data->columns);
}

void calculate_next_figure(input_data_t *input_data,
    output_data_t *output_data) {
for (size_t prof = 0; prof <= input_data->profundity; prof++) {
    printf("\nSiguiente Figura [%c]\n", input_data->next_figures[prof]);

    int num_rotations =
        get_tetris_figure_num_rotations(input_data->next_figures[prof]);

    printf("Rotaciones de la Figura [%c] : [%d]\n",
            input_data->next_figures[prof], num_rotations);

    figure_t *figure =
        get_tetris_figure(input_data->next_figures[prof], 0);

        printf("Altura [%d], Ancho [%d]\n",
            figure->height, figure->width);

        char **current_status =
        set_game_state(output_data->table, output_data->rows,
                        output_data->columns);

        validate_insert(figure, current_status, output_data);

        // Limpio templ
        free_matrix(output_data->rows, (void **)current_status);

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

        generate_game_board_txt(output_data, prof,
                                input_data->next_figures[prof]);
    }
}

char **clone_game_state(char **origin, char **destiny,
                        size_t row_count, size_t col_count) {
    /**
     * clone_char_matrix From matrix_utility
     */
    return clone_char_matrix(origin, destiny, row_count, col_count);
}

char** set_game_state(char** origin, size_t row_count, size_t col_count) {
    return generate_matrix_from_another(origin, row_count, col_count);
}

size_t get_play_score(char** table, size_t row_count, size_t col_count) {
    size_t score = 0;

    for (size_t x = 0; x < row_count; x++) {
        size_t sum = 0;
        for (size_t i = 0; i < col_count; i++) {
            if (table[x][i] != '0') {
                sum++;
            }
        }
        if (sum > 0) {
            score = score + (sum * x * x);
        }
    }

    return score;
}

void update_game_board(output_data_t *output_data, char** table) {
    size_t new_score =
        get_play_score(table, output_data->rows, output_data->columns);

    size_t current_score =
        get_play_score(output_data->table, output_data->rows,
            output_data->columns);

    if (new_score > current_score) {
        output_data->table =
            clone_game_state(table, output_data->table, output_data->rows,
                output_data->columns);
    }
}

void generate_game_board_txt(output_data_t *output_data,
        size_t profundity, char figure) {
    sscanf(&figure, "%s", output_data->figure);
    generate_output_file(profundity, output_data);
}


void validate_insert(figure_t *figure, char **current_status,
                    output_data_t *output_data) {
        size_t col = 0;

        do {
            char **temp =
            set_game_state(current_status, output_data->rows,
                        output_data->columns);

            printf("\nRealizando cálculo de inserción ...\n");

            for (size_t j = col; j < output_data->columns; j++) {
                col++;
                size_t invalid_column = 0;
                bool finish = false;
                for (size_t i = 0; i < output_data->rows; i++) {
                    if (i + figure->height > output_data->rows) {
                        printf("[Alto]\n");
                        printf("La Figura no calza en el tablero del juego!\n");
                        return;
                    }

                    if (j + figure->width > output_data->columns) {
                        printf("[Ancho]\n");
                        printf("La Figura no calza en el tablero del juego!\n");
                        return;
                    }

                    int sum = review_space(figure, temp, i, j);

                    if (sum > 0) {
                        invalid_column++;
                        break;
                    } else if ((i + figure->height < output_data->rows
                        && temp[i + figure->height][j] == '0')) {
                        int sum = review_space(figure, temp, (i + 1), j);

                        if (sum == 0) {
                            continue;
                        }
                    }

                    for (int m = 0; m < figure->height; m++) {
                        for (int n = 0; n < figure->width; n++) {
                            if (figure->value[m][n] != '0') {
                                sscanf(&figure->value[m][n], "%c", &temp[i+m][j+n]);
                            }
                        }
                    }

                        finish = true;

                        break;
                    }

                    if (finish) {
                        break;
                    }

                    if (invalid_column == output_data->columns) {
                        printf("[invalid_column]\n");
                        printf("La Figura no calza en el tablero del juego!\n");
                        return;
                    }
            }

            print_char_matrix(temp, output_data->rows,
                output_data->columns);

            update_game_board(output_data, temp);

                // Limpio templ
            free_matrix(output_data->rows, (void **)temp);
        } while (col < output_data->columns);
}


int review_space(figure_t *figure, char **temp,
                size_t row_count, size_t col_count) {
    int sum = 0;

    for (int k = 0; k < figure->height; k++) {
        for (int l = 0; l < figure->width; l++) {
            if (figure->value[k][l] != '0') {
                // https://www.delftstack.com/es/howto/c/convert-int-to-char/
                int int_value = temp[row_count+k][col_count+l] - '0';
                sum = sum + int_value;
                }
            }
    }

    return sum;
}
