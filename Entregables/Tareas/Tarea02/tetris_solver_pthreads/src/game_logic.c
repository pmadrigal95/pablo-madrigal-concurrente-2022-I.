// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

// This line is only for Visual Studio Code to recognize CLOCK_MONOTONIC
#define _POSIX_C_SOURCE 199309L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <pthread.h>
#include "game_logic.h"
#include "game_logic_utility.h"

/*
 * game_logic_utility.h
 */

void initial_status(input_data_t *input_data, size_t thread_count);

void create_output_data(input_data_t *input_data, output_data_t *output_data,
                        char **current_status);

char **set_game_state(char **origin, size_t row_count,
                      size_t col_count);

void calculate_next_figure(input_data_t *input_data,
                           output_data_t *output_data);

char **clone_game_state(char **origin, char **destiny,
                        size_t row_count, size_t col_count);

size_t get_play_score(char **table, size_t row_count, size_t col_count);

void update_game_board(output_data_t *output_data, char **table, int rot);

void generate_game_board_txt(output_data_t *output_data,
                             size_t profundity, char figure);

int review_space(figure_t *figure, char **temp,
                 size_t row_count, size_t col_count);

/**
 * Private methods
 */

void calculate_next_figure_recursive(input_data_t *input_data,
size_t current_profundity, size_t thread_count);

bool set_figure(input_data_t *input_data, size_t current_profundity,
                int num_rotations, size_t thread_count);

void insert_by_col(private_data_t *private_data,  figure_t *figure);

void validate_insert_figure(private_data_t *private_data,  figure_t *figure, size_t col);

void update_current_status(input_data_t *input_data, output_data_t *output_data,
                           size_t current_profundity);

void create_threads(input_data_t *input_data, output_data_t *output_data,
char **current_status, int num_rotations, size_t current_profundity,
 size_t thread_count);

void* run(void*);

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
void next_play(input_data_t *input_data, size_t thread_count) {
    struct timespec start_time;
        clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &start_time);

    initial_status(input_data, thread_count);

    // calculate_next_figure(input_data, output_data);

    calculate_next_figure_recursive(input_data, 0, thread_count);

    struct timespec finish_time;
    clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &finish_time);

    double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                         (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;


    free_matrix(input_data->rows, (void **)input_data->table);
    free(input_data);
    free_array((void **)input_data->next_figures);

    printf("execution time: %.9lfs\n", elapsed);
}

/*
 * Private Methods
 */

void calculate_next_figure_recursive(input_data_t *input_data,
size_t current_profundity, size_t thread_count) {
    printf("\nSiguiente Figura [%c]\n",
           input_data->next_figures[current_profundity]);

    // Obtener numero de rotaciones de la figura
    int num_rotations =
        get_tetris_figure_num_rotations
        (input_data->next_figures[current_profundity]);

    printf("Rotaciones de la Figura [%c] : [%d]\n",
           input_data->next_figures[current_profundity], num_rotations);

    bool result = set_figure(input_data, current_profundity,
    num_rotations, thread_count);

    if (current_profundity < input_data->profundity && result == true) {
        calculate_next_figure_recursive(input_data,
                                        (current_profundity + 1), thread_count);
    }
}

/**
 * @details Metodo que calcula insertar las Figuras
 * @param input_data_t *input_data
 * @param output_data_t *output_data
 * @return Realiza todos los calculo (Figuras y rotaciones en un tablero de juego)
 * y genera un txt por nivel / profundidad
 *
 */
bool set_figure(input_data_t *input_data, size_t current_profundity,
                int num_rotations, size_t thread_count) {
    bool result = false;
    // Asignacion de memoria
    output_data_t *output_data = (output_data_t *)calloc(1,
                                                         sizeof(output_data_t));

    // Matriz actual antes de intentar colocar la pieza
    char **current_status =
        set_game_state(input_data->table, input_data->rows,
                       input_data->columns);

    /**
     * Crear  Objeto de Salida
     */
    create_output_data(input_data, output_data, current_status);

    /**
     * Crear Hilos
     */
    create_threads(input_data, output_data, current_status,
    num_rotations, current_profundity, thread_count);

    if (output_data->figure_count > 0) {
        update_current_status(input_data, output_data, current_profundity);
        result = true;
    } else {
        printf("No se pueden colocar mas figuras, Fin del Juego!\n");
        result = false;
    }

    // Liberar memoria del estado previo a la figura
    free_matrix(input_data->rows, (void **)current_status);

    free_matrix(output_data->rows, (void **)output_data->table);
    free(output_data);

    return result;
}

void update_current_status(input_data_t *input_data, output_data_t *output_data,
                           size_t current_profundity) {
    input_data->table =
        clone_game_state(output_data->table, input_data->table,
                         output_data->rows, output_data->columns);
    // Generar archivo del nivel
    output_data->figure_count = 0;
    // Generar archivo del nivel
    generate_game_board_txt(output_data, current_profundity,
                            input_data->next_figures[current_profundity]);
}

void insert_by_col(private_data_t *private_data,  figure_t *figure) {
    // Mapeo Ciclico
    for (size_t col = private_data->thread_num;
    col < private_data->input_data->columns;
    col = col + private_data->num_threads) {
        validate_insert_figure(private_data, figure, col);
    }
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
void validate_insert_figure(private_data_t *private_data,  figure_t *figure,
size_t col) {
    // Generar un tablero temporal para la insercion de la Figura
    char **temp =
        set_game_state(private_data->current_status,
        private_data->input_data->rows, private_data->input_data->columns);

    printf("\nRealizando cálculo de inserción ...\n");

    // Se recorre Primero las columnas
    for (size_t j = col;
        j < private_data->input_data->columns; j++) {
        printf("Columna [%zu]\n", j);
        size_t invalid_column = 0;
        bool finish = false;

        // Validacion de espacio
        for (size_t i = 0; i < private_data->input_data->rows; i++) {
            if (i + figure->height > private_data->input_data->rows) {
                printf("[Alto]\n");
                printf("La Figura no calza en el tablero del juego!\n");
                return;
            }

            // Validacion de espacio
            if (j + figure->width > private_data->input_data->columns) {
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
            } else if (
                (i + figure->height < private_data->input_data->rows
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
                        sscanf(&figure->value[m][n], "%c", &temp[i + m][j + n]);
                    }
                }
            }

            // Matriz resultante luego del intento
            print_char_matrix(temp, private_data->input_data->rows,
                              private_data->input_data->columns);

            shared_data_t* shared_data = private_data->shared_data;
            // Valida si debe actualizar la partida del juego
            pthread_mutex_lock(&shared_data->can_review_score);
            update_game_board(private_data->output_data, temp,
            private_data->num_rotations);
            pthread_mutex_unlock(&shared_data->can_review_score);

            finish = true;

            break;
        }

        if (finish) {
            break;
        }

        /* si no logro colocar la pieza y ya no hay tablero de juego
         * Se muestra un error
         */
        if (invalid_column == private_data->input_data->columns) {
            printf("[invalid_column]\n");
            printf("La Figura no calza en el tablero del juego!\n");
            return;
        }
    }

    // Libera la memoria
    free_matrix(private_data->input_data->rows, (void **)temp);
}

void create_threads(input_data_t *input_data, output_data_t *output_data,
char **current_status, int num_rotations, size_t current_profundity,
 size_t thread_count) {
    //creacion de hilos
    pthread_t* threads = (pthread_t*)calloc(thread_count, sizeof(pthread_t));

    if (threads) {
        private_data_t *private_data = (private_data_t *)
            calloc(thread_count, sizeof(private_data_t));

        shared_data_t *shared_data = (shared_data_t *)calloc(1,
                                                             sizeof(shared_data_t));

        if (shared_data && private_data) {
            pthread_mutex_init(&shared_data->can_review_score, NULL);

            for (size_t index = 0; index < thread_count; ++index) {
                // Asignacion de valores
                private_data[index].input_data = input_data;
                private_data[index].output_data = output_data;
                private_data[index].current_status = current_status;
                private_data[index].num_rotations = num_rotations;
                private_data[index].current_profundity = current_profundity;
                private_data[index].thread_num = index;
                private_data[index].num_threads = thread_count;
                private_data[index].shared_data = shared_data;

                if (pthread_create(&threads[index], NULL, run,
                                   &private_data[index]) != EXIT_SUCCESS) {
                    fprintf(stderr, "Could not create thread %zu.\n", index);
                    exit(EXIT_FAILURE);
                }
            }

            for (size_t index = 0; index < thread_count; ++index) {
                pthread_join(threads[index], /*value_ptr*/ NULL);
            }
            free(private_data);

            pthread_mutex_destroy(&shared_data->can_review_score);
            free(shared_data);
        } else {
            fprintf(stderr, "Unable to allocate memory for %zu threads\n",
                    thread_count);
            exit(EXIT_FAILURE);
        }

        free(threads);

    } else {
        fprintf(stderr, "Unable to allocate memory for %zu threads\n",
            thread_count);
         exit(EXIT_FAILURE);
    }
}

void* run(void* data) {
    private_data_t *private_data = (private_data_t *)data;

    // Realizar intentos por rotacion y por figura
    for (int rot = 0; rot < private_data->num_rotations; rot++) {
        // Obtener Figura y su rotacion actual
        figure_t *figure =
            get_tetris_figure(private_data->input_data->next_figures
            [private_data->current_profundity], rot);

        printf("Altura [%d], Ancho [%d]\n",
               figure->height, figure->width);

        // Imprimir la Figura actual
        print_char_matrix(figure->value, figure->height,
                          figure->width);
        // Intenta colocar la Figura en la mejor posicion
        insert_by_col(private_data, figure);
    }

    return NULL;
}
