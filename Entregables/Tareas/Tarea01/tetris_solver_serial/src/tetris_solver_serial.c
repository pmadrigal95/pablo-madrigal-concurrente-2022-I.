// Copyright 2022 Pablo Madrigal <PABLO.MADRIGALRAMIREZ@ucr.ac.cr>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char *filename = "../test/test01.txt";

int main() {
    FILE *in_file = fopen(filename, "r");
    int line = 0;
    if (!in_file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char *file_contents = malloc(sb.st_size);

    while (fscanf(in_file, "%[^\n] ", file_contents) != EOF) {
        line++;
        printf("%d : %s\n", line, file_contents);
    }

    fclose(in_file);
    exit(EXIT_SUCCESS);
}
