// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

// Referencia https://gist.github.com/miguelpais/388199

#include <stdio.h>
#include <stdlib.h>
#include "list_utility.h"
#include "matrix_utility.h"

char** generate_matrix_from_another(char** origin,
                        size_t row_count, size_t col_count);

void print_char_matrix(char ** matrix, size_t row_count, size_t col_count);

void free_matrix(const size_t row_count, void **matrix);


void init_list(list *l) {
    l->first = NULL;
    l->nitem = 0;
}

item *create_list(char** origin, size_t row_count, size_t col_count) {
    item *it = malloc(sizeof(item));
    it->table = generate_matrix_from_another(origin, row_count, col_count);
    it->next = NULL;
    return it;
}

void insert_list(list *l, char** origin, size_t row_count, size_t col_count) {
    item *it = create_list(origin, row_count, col_count);
    it->next = l->first;
    l->first = it;
    l->nitem++;
}

void print_list(list *l, size_t row_count, size_t col_count) {
    item *it;
    printf("Intentos realizados: %d:\n", l->nitem);
    for (it = l->first; it != NULL; it = it->next) {
        print_char_matrix(it->table, row_count, col_count);
    }
}

void clear_list(list *l, size_t row_count) {
    item *it;
    while ((it = l->first) != NULL) {
        l->first = l->first->next;
        free_matrix(row_count, (void **)it->table);
        free(it);
    }
    l->nitem = 0;
}

void clone_list(list* origin, list* destiny,
                size_t row_count, size_t col_count) {
    clear_list(destiny, row_count);

    item *it;
    for (it = origin->first; it != NULL; it = it->next) {
        insert_list(destiny, it->table, row_count, col_count);
    }
}
