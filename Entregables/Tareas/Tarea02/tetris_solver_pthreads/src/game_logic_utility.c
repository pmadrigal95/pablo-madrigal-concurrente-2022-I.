// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "file_utility.h"
#include "matrix_utility.h"
#include "game_logic_utility.h"
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


/**
 * @details Revisa estado actual del juego y crea la estructura final
 * @param input_data_t ptr
 * @param output_data ptr
 *
 */
void initial_status(input_data_t *input_data) {
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

/**
 * @details Crea la estructura final que se utiliza para crear los archivos TXT por figura
 * @param input_data_t ptr
 * @param output_data ptr
 *
 */
void create_output_data(input_data_t *input_data, output_data_t *output_data,
char **current_status) {
    output_data->identifier = input_data->identifier;
    output_data->rows = input_data->rows;
    output_data->columns = input_data->columns;
    output_data->figure_count = 0;

     output_data->table =
        set_game_state(current_status, input_data->rows,
                        input_data->columns);
}



/**
 * @details Clona tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return Clona tablero de juego en el destino
 *
 */
char **clone_game_state(char **origin, char **destiny,
                        size_t row_count, size_t col_count) {
    /**
     * clone_char_matrix From matrix_utility
     */
    return clone_char_matrix(origin, destiny, row_count, col_count);
}

/**
 * @details Crea un nuevo tablero de juego apartir de uno existente
 * @param char** origin
 * @param size_t row_count
 * @param size_t col_count
 * @return nuevo tablero de juego
 *
 */
char** set_game_state(char** origin, size_t row_count, size_t col_count) {
    return generate_matrix_from_another(origin, row_count, col_count);
}

/**
 * @details Logica que retorna los puntos de un tablero de juego
 * @param char** table
 * @param size_t row_count
 * @param size_t col_count
 * @return puntos de un tablero de juego
 *
 */
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

/**
 * @details Validar si el intento actual tiene mejor puntuaje que el estado del juego actual
 * SI tiene mas punto procede a reemplazar el juego actual por la nueva jugada con mejor puntuaje
 * @param output_data_t *output_data
 * @param char** table
 * @return nuevo estado actual de la partida
 *
 */
void update_game_board(output_data_t *output_data, char** table, int rot) {
    size_t new_score =
        get_play_score(table, output_data->rows, output_data->columns);

    size_t current_score =
        get_play_score(output_data->table, output_data->rows,
            output_data->columns);

    if (new_score > current_score) {
        output_data->rotation = rot;
        output_data->table =
            clone_game_state(table, output_data->table, output_data->rows,
                output_data->columns);
    }
}

/**
 * @details Enviar la informacion necesaria para generar el txt de salida
 * @param output_data_t *output_data
 * @param size_t profundity
 * @param char figure
 * @return archivo txt de la profundidad, se genera en la carpeta bin
 *
 */
void generate_game_board_txt(output_data_t *output_data,
        size_t profundity, char figure) {
    sscanf(&figure, "%s", output_data->figure);
    generate_output_file(profundity, output_data);
}



/**
 * @details Metodo que revisa de acuerdo a su posicion, si puede insertar la Figura y sus dimensiones
 * @param figure_t *figure
 * @param char **temp
 * @param size_t row_count
 * @param size_t col_count
 * @return Verificacion de los espacios, si devuelve cero puede insertar
 *
 */
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
