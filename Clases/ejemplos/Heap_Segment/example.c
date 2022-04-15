#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

void *run(void *);

int main(int argc, char **arg)
{

    size_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

    if (argc == 2)
    {
        if (sscanf(arg[1], "%zu", &thread_count) != 1 || errno)
        {
            fprintf(stderr, 'error: invalid thread count!\n');
            return EXIT_FAILURE;
        }
    }

    pthread_t *threads = (pthread_t *)malloc(thread_count * sizeof(pthread_t));

    if (threads)
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            if (pthread_create(&threads[i], NULL, run, (void *)i) != EXIT_SUCCESS)
            {
                return EXIT_FAILURE;
            }
        }
        printf("Hello from the main thread\n");

        for (size_t i = 0; i < thread_count; ++i)
        {
            pthread_join(threads[i], NULL);
        }

        free(threads);
    }
    else
    {
        fprintf(stderr, "Could not allocate memory for %zu threads\n", thread_count);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void *run(void *params)
{
    printf("Hello from the secondary thread %zu!\n", (size_t)params);
    return NULL;
}