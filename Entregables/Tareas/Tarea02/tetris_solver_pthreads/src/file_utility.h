// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_FILE_UTILITY_H_
#define SRC_FILE_UTILITY_H_

#include "structures.h"

/**
 * @brief Metodo que se encarga de leer un txt de entrada y almacena la informacion en memoria
 * @details Metodo que se encarga de leer un txt de entrada y almacena la informacion en puntero input_data_t
 * @param puntero del archivo TXT
 * @param puntero input_data_t
 * @return Si el fichero de entrada no es valido termina la ejecucion del programa con un error!
 *
 */
void get_input_data(char *filename, input_data_t* input_data);

/**
 * @brief Metodo que se encarga de generar un txt de Salida con la informacion generada por Figura
 * @details Metodo que se encarga de generar un txt de Salida con la informacion generada por profundidad
 * @param profundity nivel de profundida del Struct
 * @param puntero output_data_t
 * @return Si el fichero no es valido termina la ejecucion del programa con un error!
 *
 */
void generate_output_file(size_t profundity, output_data_t *output_data);

#endif  // SRC_FILE_UTILITY_H_
