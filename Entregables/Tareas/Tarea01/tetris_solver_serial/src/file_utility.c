// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "file_utility.h"
#include "matrix_utility.h"

bool validate_number(char item, int type);
void print_error_message(input_data_t *input_data, int type);
void *create_array(size_t row_count, size_t element_size);
void free_matrix(const size_t row_count, void **matrix);
void free_array(void *array);
void validate_incomming_txt(FILE *in_file, char *filename);
void write_output_data(char *filename, output_data_t *output_data);
void assign_initial_values(FILE *in_file, input_data_t *input_data);
void assign_incomming_array(FILE *in_file, input_data_t *input_data);
void assign_incomming_matrix(FILE *in_file, input_data_t *input_data);
void generate_output_file(size_t profundity, output_data_t *output_data);
void **create_matrix(size_t row_count, size_t col_count, size_t element_size);

/*
* Public Methods
*/

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

void generate_output_file(size_t profundity, output_data_t *output_data) {
    char filename[] = "tetris_play_X.txt";
    char charValue = profundity+'0';
    int i = 0;

    while (filename[i] != '\0') {
        if (filename[i] == 'X') {
            filename[i] = charValue;
        }
        i++;
    }

    char *filename_pt = filename;

    printf("Creación del Fichero [%s]\n", filename);

    write_output_data(filename_pt, output_data);
}

/*
* Private Methods
*/

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
    const unsigned ZERO = 0;

    fscanf(in_file, "%zu", &input_data->identifier);

    if (!input_data->identifier) {
        print_error_message(input_data, 0);
    }

    fscanf(in_file, "%zu", &input_data->profundity);

    if (input_data->profundity == (size_t)-1) {
        print_error_message(input_data, 0);
    }

    fscanf(in_file, "%zu", &input_data->rows);

    if (!input_data->rows || input_data->rows <= ZERO ||
        input_data->rows == (size_t)-1) {
        print_error_message(input_data, 0);
    }

    fscanf(in_file, "%zu", &input_data->columns);

    if (!input_data->columns || input_data->columns <= ZERO ||
        input_data->columns == (size_t)-1) {
        print_error_message(input_data, 0);
    }

    assign_incomming_matrix(in_file, input_data);

    fscanf(in_file, "%zu", &input_data->number_of_figures);

    if (!input_data->number_of_figures ||
        input_data->number_of_figures <= input_data->profundity ||
        input_data->number_of_figures == (size_t)-1) {
        print_error_message(input_data, 0);
    }

    assign_incomming_array(in_file, input_data);
}

void assign_incomming_matrix(FILE *in_file, input_data_t *input_data) {
    input_data->table = (char **)
        create_matrix((input_data->rows + 1),
        (input_data->columns + 1), sizeof(char));

    for (size_t row = 0; row < input_data->rows; row++) {
        char temp[input_data->columns];
        fscanf(in_file, "%s", temp);

        if (strlen(temp) == input_data->columns) {
            for (size_t column = 0; column < input_data->columns; column++) {
                char item = temp[column];
                bool result = validate_number(item, 1);
                if (result == true) {
                    input_data->table[row][column] = item;
                } else {
                    print_error_message(input_data, 1);
                }
            }
        } else {
            print_error_message(input_data, 1);
        }
    }
}

void assign_incomming_array(FILE *in_file, input_data_t *input_data) {
    input_data->next_figures = (char *)
        create_array((input_data->number_of_figures + 1) , sizeof(char));

    if (input_data->profundity <= input_data->number_of_figures) {
        for (size_t i = 0; i < input_data->number_of_figures; i++) {
            fscanf(in_file, "%s", &input_data->next_figures[i]);

            bool result = validate_number(input_data->next_figures[i], 2);
                if (result == false) {
                    print_error_message(input_data, 2);
                }
        }
    } else {
        print_error_message(input_data, 2);
    }
}

void write_output_data(char *filename, output_data_t *output_data) {
// Adaptacion -> https://parzibyte.me/blog/2019/10/16/escribir-archivo-con-c-usando-fprintf/
    FILE *in_file = fopen(filename, "wt");

    fprintf(in_file, "%zu\n", output_data->identifier);
    fprintf(in_file, "%s\n", output_data->figure);
    fprintf(in_file, "%zu\n", output_data->rotation);
    fprintf(in_file, "%zu\n", output_data->rows);
    fprintf(in_file, "%zu\n", output_data->columns);

    for (size_t row = 0; row < output_data->rows; row++) {
        for (size_t col = 0; col < output_data->columns; col++) {
            fprintf(in_file, "%c", output_data->table[row][col]);
        }
        fprintf(in_file, "\n");
    }

    fclose(in_file);

    printf("Cerrar Fichero de Escritura [%s]\n", filename);
}

bool validate_number(char item, int type) {
    bool result = false;

    if (type == 1) {
            switch (item) {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                result = true;
                break;
            default:
                result = false;
                break;
        }
    } else {
        switch (item) {
            case 'I':
            case 'Z':
            case 'S':
            case 'L':
            case 'J':
            case 'O':
            case 'T':
                result = true;
                break;
            default:
                result = false;
                break;
        }
    }
    return result;
}

void free_error_matrix(input_data_t *input_data, int type) {
    /**
     * Liberar Memoria de la Estructura
     */
    if (type == 2) {
        free_array((void **)input_data->next_figures);
    }

    free_matrix(input_data->rows,
                (void **)input_data->table);
}

void print_error_message(input_data_t *input_data, int type) {
    if (type > 0) {
        free_error_matrix(input_data, type);
    }

    free(input_data);
    printf("Formato del Tablero de Juego incorrecto\n");
    exit(EXIT_FAILURE);
}
