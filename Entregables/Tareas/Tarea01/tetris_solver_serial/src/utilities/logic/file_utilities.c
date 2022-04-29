// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include "file_utilities.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stddef.h>
#include <string.h>

void get_input_data(char *filename, input_data_t *input_data)
{
    // Adaptacion -> https://www.delftstack.com/es/howto/c/fscanf-line-by-line-in-c/

    printf("Lectura del Archivo [%s]\n", filename);

    FILE *in_file = fopen(filename, "r");

    if (!in_file)
    {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1)
    {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("Asignacion de valores iniciales\n");

    fscanf(in_file, "%zu", &input_data->identifier);

    fscanf(in_file, "%zu", &input_data->profundity);

    fscanf(in_file, "%zu", &input_data->rows);

    fscanf(in_file, "%zu", &input_data->columns);

    input_data->table = (char **)malloc((input_data->rows + 1) * sizeof(char *));

    for (size_t index = 0; index < input_data->rows; index++)
    {
        input_data->table[index] = (char *)malloc((input_data->columns + 1) * sizeof(char));
    }

    for (size_t row = 0; row < input_data->rows; row++)
    {
        char temp[100];
        fscanf(in_file, "%s", temp);

        if (strlen(temp) == input_data->columns)
        {
            for (size_t column = 0; column < input_data->columns; column++)
            {
                char item = temp[column];
                input_data->table[row][column] = item;
            }
        }
        else
        {
            printf("Formato del tablero incorrecto %lu\n", strlen(temp));
            exit(EXIT_FAILURE);
        }
    }

    fscanf(in_file, "%zu", &input_data->number_of_figures);

    input_data->next_figures = (char *)malloc(sizeof(char) * input_data->number_of_figures);

    if (input_data->profundity <= input_data->number_of_figures)
    {
        for (size_t i = 0; i < input_data->number_of_figures; i++)
        {
            fscanf(in_file, "%s", &input_data->next_figures[i]);
        }
        
    }
    else
    {
        printf("Formato del tablero incorrecto\n");
        exit(EXIT_FAILURE);
    }

    fclose(in_file);

    printf("Cerrar Fichero de Lectura Inicial\n");
}
