// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <sys/stat.h>
#include "file_utility.h"
#include "matrix_utility.h"

void validate_incomming_txt(FILE *in_file, char *filename);
void assign_incomming_matrix(FILE *in_file, input_data_t *input_data);
void assign_incomming_array(FILE *in_file, input_data_t *input_data);
void assign_initial_values(FILE *in_file, input_data_t *input_data);
void **create_matrix(size_t row_count, size_t col_count, size_t element_size);
void *create_array(size_t row_count, size_t element_size);

void get_input_data(char *filename, input_data_t *input_data) {
    // Adaptacion -> https://www.delftstack.com/es/howto/c/fscanf-line-by-line-in-c/

    printf("Lectura del Archivo [%s]\n", filename);

    FILE *in_file = fopen(filename, "r");

    validate_incomming_txt(in_file, filename);

    printf("Asignacion de valores iniciales\n");

    assign_initial_values(in_file, input_data);

    fclose(in_file);

    printf("Cerrar Fichero de Lectura Inicial\n");
}


void validate_incomming_txt(FILE *in_file, char *filename) {
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }
}


void assign_initial_values(FILE *in_file, input_data_t *input_data) {
    fscanf(in_file, "%zu", &input_data->identifier);

    fscanf(in_file, "%zu", &input_data->profundity);

    fscanf(in_file, "%zu", &input_data->rows);

    fscanf(in_file, "%zu", &input_data->columns);

    assign_incomming_matrix(in_file, input_data);

    fscanf(in_file, "%zu", &input_data->number_of_figures);

    assign_incomming_array(in_file, input_data);
}

void assign_incomming_matrix(FILE *in_file, input_data_t *input_data) {
    input_data->table = (char **)
        create_matrix((input_data->rows + 1),
        (input_data->columns + 1), sizeof(char));

    for (size_t row = 0; row < input_data->rows; row++) {
        char temp[100];
        fscanf(in_file, "%s", temp);

        if (strlen(temp) == input_data->columns) {
            for (size_t column = 0; column < input_data->columns; column++) {
                char item = temp[column];
                input_data->table[row][column] = item;
            }
        } else {
            printf("Formato del tablero incorrecto %lu\n", strlen(temp));
            exit(EXIT_FAILURE);
        }
    }
}

void assign_incomming_array(FILE *in_file, input_data_t *input_data) {
    input_data->next_figures = (char *)
        create_array((input_data->number_of_figures + 1) , sizeof(char));

    if (input_data->profundity <= input_data->number_of_figures) {
        for (size_t i = 0; i < input_data->number_of_figures; i++) {
            fscanf(in_file, "%s", &input_data->next_figures[i]);
        }
    } else {
        printf("Formato del tablero incorrecto\n");
        exit(EXIT_FAILURE);
    }
}
