#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* hello_run(void*);
void* goodBye_run(void*);

int main() {

    size_t value = sysconf(_SC_NPROCESSORS_ONLN);

    pthread_t hello_thread, goodBye_thread;

    int hello_t = pthread_create(&hello_thread, NULL /*attr*/, hello_run, (void*)value);
    int goodBye_t = pthread_create(&goodBye_thread, NULL /*attr*/, goodBye_run, (void*)value);

    if (hello_t == EXIT_SUCCESS && goodBye_t == EXIT_SUCCESS) {
        printf("Hello and goodbye world! %zu\n", value);
        pthread_join(hello_thread, NULL);
        pthread_join(goodBye_thread, NULL);
    } else {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void* hello_run(void* param) {
    size_t value = (size_t)param;
    printf("Hello world! %zu\n", value);

    return NULL;
}

void* goodBye_run(void* param) {
    size_t value = (size_t)param;
    printf("Goodbye world! %zu\n", value);

    return NULL;
}