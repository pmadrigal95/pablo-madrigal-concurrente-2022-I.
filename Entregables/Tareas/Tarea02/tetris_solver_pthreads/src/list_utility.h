// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#ifndef SRC_LIST_UTILITY_H_
#define SRC_LIST_UTILITY_H_

struct _item {
    char **table;
    struct _item *next;
};

typedef struct _item item;

struct _list {
    item *first;
    int nitem;
};

typedef struct _list list;


void init_list(list *l);

item *create_list(char** origin,
                        size_t row_count, size_t col_count);

void insert_list(list *l, char** origin,
                        size_t row_count, size_t col_count);

void print_list(list *l, size_t row_count, size_t col_count);

void clear_list(list *l, size_t row_count);

void clone_list(list* origin, list* destiny,
                size_t row_count, size_t col_count);

#endif  // SRC_LIST_UTILITY_H_
