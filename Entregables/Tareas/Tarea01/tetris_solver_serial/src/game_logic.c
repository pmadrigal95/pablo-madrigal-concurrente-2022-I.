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

/**
 * @brief Compute next move from input_data_t ptr
 * @details Returns a input_data_t ptr representing the input data based on the given txt file
 * @param input_data_t ptr 
 * @return Best possible move
 *
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

/**
 * @details Revisa estado actual del juego y crea la estructura final
 * @param input_data_t ptr
 * @param output_data ptr
 *
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

/**
 * @details Crea la estructura final que se utiliza para crear los archivos TXT por figura
 * @param input_data_t ptr
 * @param output_data ptr
 *
 */
void create_output_data(input_data_t *input_data, output_data_t *output_data) {
    output_data->identifier = input_data->identifier;
    output_data->rows = input_data->rows;
    output_data->columns = input_data->columns;

     output_data->table =
        set_game_state(input_data->table, input_data->rows,
                        input_data->columns);
}

/**
 * @details Metodo que calcula insertar las Figuras
 * @param input_data_t *input_data
 * @param output_data_t *output_data
 * @return Realiza todos los calculo (Figuras y rotaciones en un tablero de juego)
 * y genera un txt por nivel / profundidad
 *
 */
void calculate_next_figure(input_data_t *input_data,
    output_data_t *output_data) {
for (size_t prof = 0; prof <= input_data->profundity; prof++) {
    // Matriz actual antes de intentar colocar la pieza
    char **current_status =
        set_game_state(output_data->table, output_data->rows,
                        output_data->columns);

    output_data->figure_count = 0;

    printf("\nSiguiente Figura [%c]\n", input_data->next_figures[prof]);

    // Obtener numero de rotaciones de la figura
    int num_rotations =
        get_tetris_figure_num_rotations(input_data->next_figures[prof]);

    printf("Rotaciones de la Figura [%c] : [%d]\n",
            input_data->next_figures[prof], num_rotations);

    // Realizar intentos por rotacion y por figura
    for (int rot = 0; rot < num_rotations; rot++) {
        // Obtener Figura y su rotacion actual
        figure_t *figure =
            get_tetris_figure(input_data->next_figures[prof], rot);

        printf("Altura [%d], Ancho [%d]\n",
            figure->height, figure->width);

        // Imprimir la Figura actual
        print_char_matrix(figure->value, figure->height,
                figure->width);

        // Intenta colocar la Figura en la mejor posicion
        validate_insert(figure, current_status, output_data);
    }
        // Liberar memoria del estado previo a la figura
        free_matrix(output_data->rows, (void **)current_status);

        if (output_data->figure_count > 0) {
            // Generar archivo del nivel
            generate_game_board_txt(output_data, prof,
                                input_data->next_figures[prof]);
            output_data->figure_count = 0;
        } else {
            printf("No se pueden colocar mas figuras, Fin del Juego!\n");
            break;
        }
    }
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
 * @details Metodo que calcula insertar Una Figura en una posicion en una matriz dada
 * @param figure_t *figure,
 * @param char **current_status
 * @param output_data_t *output_data
 * @return Valida si la jugada tiene mas puntos que la actual y
 * actualiza el output_data
 *
 */
void validate_insert(figure_t *figure, char **current_status,
                    output_data_t *output_data) {
        /* Se intenta colocar la pieza de arriba hacia abajo 
         * empezando por la columna 0
        */
        size_t col = 0;

        // realizar intento en cada columna
        do {
            // Generar un tablero temporal para la insercion de la Figura
            char **temp =
            set_game_state(current_status, output_data->rows,
                        output_data->columns);

            printf("\nRealizando cálculo de inserción ...\n");

            // Se recorre Primero las columnas
            for (size_t j = col; j < output_data->columns; j++) {
                col++;
                size_t invalid_column = 0;
                bool finish = false;

                // Validacion de espacio
                for (size_t i = 0; i < output_data->rows; i++) {
                    if (i + figure->height > output_data->rows) {
                        printf("[Alto]\n");
                        printf("La Figura no calza en el tablero del juego!\n");
                        return;
                    }

                    // Validacion de espacio
                    if (j + figure->width > output_data->columns) {
                        printf("[Ancho]\n");
                        printf("La Figura no calza en el tablero del juego!\n");
                        return;
                    }

                    /* Se procede a validar en la posicion actual,
                     * si puede realizar la insercion
                    */
                    int sum = review_space(figure, temp, i, j);

                    /* Si la suma es mayor a cero significa que no hay espacio suficiente,
                     * Se cambia de columna y empieza de nuevo
                    */
                    if (sum > 0) {
                        invalid_column++;
                        break;
                    } else if ((i + figure->height < output_data->rows
                        && temp[i + figure->height][j] == '0')) {
                        /* Se verifica si puede seguir cayendo,
                        * y se valida que la siguiente fila tenga espacio antes de cambiar de fila
                        */
                        int sum = review_space(figure, temp, (i + 1), j);

                        if (sum == 0) {
                            continue;
                        }
                    }

                    // Se procede a insertar la pieza
                    for (int m = 0; m < figure->height; m++) {
                        for (int n = 0; n < figure->width; n++) {
                            if (figure->value[m][n] != '0') {
                                sscanf(&figure->value[m][n], "%c", &temp[i+m][j+n]);
                            }
                        }
                    }

                    // Matriz resultante luego del intento
                    print_char_matrix(temp, output_data->rows,
                        output_data->columns);

                    // Valida si debe actualizar la partida del juego
                    update_game_board(output_data, temp);

                    output_data->figure_count++;

                    finish = true;

                    break;
                }

                if (finish) {
                    break;
                }

                /* si no logro colocar la pieza y ya no hay tablero de juego
                    * Se muestra un error
                */
                if (invalid_column == output_data->columns) {
                    printf("[invalid_column]\n");
                    printf("La Figura no calza en el tablero del juego!\n");
                    return;
                }
            }

            // Libera la memoria
            free_matrix(output_data->rows, (void **)temp);
        } while (col < output_data->columns);
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