// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "./file_utility.h"
#include "./matrix_utility.h"

#define INVALID_VALUE -1

#define FREE_STRUCT 0
#define FREE_MATRIX 1
#define FREE_ALL 2

#define VALIDATE_MATRIX 1
#define VALIDATE_FIGURE 2

/*
* matrix_utility.h
*/

void free_array(void *array);
void free_matrix(const size_t row_count, void **matrix);
void *create_array(size_t row_count, size_t element_size);
void **create_matrix(size_t row_count, size_t col_count, size_t element_size);

/*
* Private
*/

bool validate_number(char item, int type);
void validate_incomming_txt(FILE *in_file, char *filename);
void print_error_message(input_data_t *input_data, int type);
void write_output_data(char *filename, output_data_t *output_data);
void assign_initial_values(FILE *in_file, input_data_t *input_data);
void assign_incomming_array(FILE *in_file, input_data_t *input_data);
void assign_incomming_matrix(FILE *in_file, input_data_t *input_data);
void generate_output_file(size_t profundity, output_data_t *output_data);

/*
* Public Methods
*/

/**
 * @brief Metodo que se encarga de leer un txt de entrada y almacena la informacion en memoria
 * @details Metodo que se encarga de leer un txt de entrada y almacena la informacion en puntero input_data_t
 * @param puntero del archivo TXT
 * @param puntero input_data_t
 * @return Si el fichero de entrada no es valido termina la ejecucion del programa con un error!
 *
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

/**
 * @brief Metodo que se encarga de generar un txt de Salida con la informacion generada por Figura
 * @details Genera el nombre apropiado 
 * @param profundity nivel de profundida del Struct
 * @param puntero output_data_t
 * @return Si el fichero no es valido termina la ejecucion del programa con un error!
 *
 */
void generate_output_file(size_t profundity, output_data_t *output_data) {
    char filename[50];

    sprintf(filename, "tetris_play_%zu.txt", profundity);


    char *filename_pt = filename;

    printf("Creación del Fichero [%s]\n", filename);

    /**
     * @details Metodo que se encarga de generar un txt de Salida con la informacion generada por Figura
     */
    write_output_data(filename_pt, output_data);
}

/*
* Private Methods
*/

/**
 * @details Validar txt de entrada sea valido
 * @param FILE *in_file linea del archivo a utilizar
 * @param char *filename
 * @return si no es correcto retorna error
 *
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

/**
 * @details Assignar valores al struct
 * @param FILE *in_file linea del archivo a utilizar
 * @param input_data_t *input_data
 * @return valores del fichero a memoria / error de formato
 *
*/
void assign_initial_values(FILE *in_file, input_data_t *input_data) {
    const unsigned ZERO = 0;

    fscanf(in_file, "%zu", &input_data->identifier);

    if (!input_data->identifier) {
        print_error_message(input_data, FREE_STRUCT);
    }

    fscanf(in_file, "%zu", &input_data->profundity);

    if (input_data->profundity == (size_t)INVALID_VALUE) {
        print_error_message(input_data, FREE_STRUCT);
    }

    fscanf(in_file, "%zu", &input_data->rows);

    if (!input_data->rows || input_data->rows <= ZERO ||
        input_data->rows == (size_t)INVALID_VALUE) {
        print_error_message(input_data, FREE_STRUCT);
    }

    fscanf(in_file, "%zu", &input_data->columns);

    if (!input_data->columns || input_data->columns <= ZERO ||
        input_data->columns == (size_t)INVALID_VALUE) {
        print_error_message(input_data, FREE_STRUCT);
    }

    assign_incomming_matrix(in_file, input_data);

    fscanf(in_file, "%zu", &input_data->number_of_figures);

    if (!input_data->number_of_figures ||
        input_data->number_of_figures <= input_data->profundity ||
        input_data->number_of_figures == (size_t)INVALID_VALUE) {
        print_error_message(input_data, FREE_STRUCT);
    }

    assign_incomming_array(in_file, input_data);
}

/**
 * @details Ingresar los datos a la matriz
 * @param FILE *in_file linea del archivo a utilizar
 * @param input_data_t *input_data
 * @return matriz del estado actual de la jugada
 *
*/
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
                bool result = validate_number(item, VALIDATE_MATRIX);
                if (result == true) {
                    input_data->table[row][column] = item;
                } else {
                    print_error_message(input_data, FREE_MATRIX);
                }
            }
        } else {
            print_error_message(input_data, FREE_MATRIX);
        }
    }
}

/**
 * @details Ingresar los datos al vector de Figuras
 * @param FILE *in_file linea del archivo a utilizar
 * @param input_data_t *input_data
 * @return Vector de Siguientes Figuras
 *
*/
void assign_incomming_array(FILE *in_file, input_data_t *input_data) {
    input_data->next_figures = (char *)
        create_array((input_data->number_of_figures + 1) , sizeof(char));

    if (input_data->profundity <= input_data->number_of_figures) {
        for (size_t i = 0; i < input_data->number_of_figures; i++) {
            fscanf(in_file, "%s", &input_data->next_figures[i]);

            bool result = validate_number
            (input_data->next_figures[i], VALIDATE_FIGURE);
                if (result == false) {
                    print_error_message(input_data, FREE_ALL);
                }
        }
    } else {
        print_error_message(input_data, FREE_ALL);
    }
}

/**
 * @details Validar datos de entrada matriz / vector de figuras
 * @param char item -> caracter a validar
 * @param int type -> validar que nivel de profundidad se requiere liberar la memoria
 * 1 -> Valores de la matriz
 * 2 -> valores de la Figura
 * @return Retorna valor booleano TRUE -> valor valido / False -> valor invalido
 *
*/
bool validate_number(char item, int type) {
    bool result = false;

    if (type == VALIDATE_MATRIX) {
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

/**
 * @details Liberar Memoria de la Estructura
 * @param input_data_t *input_data Para liberar la memoria dinamica
 * @param int type -> validar que nivel de profundidad se requiere liberar la memoria
 * 0 -> solo la struct
 * 1 -> table
 * 2 -> table & Figures
 * @return Mensaje de error y termina la ejecucion del sistema
 *
*/
void free_error_matrix(input_data_t *input_data, int type) {
    /**
     * Liberar Memoria de la Estructura
     */
    if (type == FREE_ALL) {
        free_array((void **)input_data->next_figures);
    }

    free_matrix(input_data->rows,
                (void **)input_data->table);
}

/**
 * @details Mensaje de error y termina la ejecucion del sistema
 * @param input_data_t *input_data Para liberar la memoria dinamica
 * @param int type -> validar que nivel de profundidad se requiere liberar la memoria
 * 0 -> solo la struct
 * 1 -> table
 * 2 -> table & Figures
 * @return Mensaje de error y termina la ejecucion del sistema
 *
*/
void print_error_message(input_data_t *input_data, int type) {
    if (type > FREE_STRUCT) {
        free_error_matrix(input_data, type);
    }

    free(input_data);
    printf("Formato del Tablero de Juego incorrecto\n");
    exit(EXIT_FAILURE);
}

/**
 * @brief Metodo que se encarga de generar un txt de Salida con la informacion generada por Figura
 * @details Genera el nombre apropiado 
 * @param profundity nivel de profundida del Struct
 * @param puntero output_data_t
 * @return Si el fichero no es valido termina la ejecucion del programa con un error!
 *
 */
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
