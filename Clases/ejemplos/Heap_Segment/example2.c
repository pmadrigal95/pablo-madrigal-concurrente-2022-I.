#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *run(void *data);

int main(int argc, char *argv[])
{

    size_t thread_count = sysconf(_SC_NPROCESSORS_ONLN);

    if (argc == 2)
    {
        if (sscanf(argv[1], "%zu", &thread_count) != 1 || errno)
        {
            fprintf(stderr, "error: invalid thread count!\n");
            return EXIT_FAILURE;
        }
    }

    pthread_t *threads = (pthread_t *)malloc(thread_count * sizeof(pthread_t));

    if (threads)
    {
        for (size_t index = 0; index < thread_count; index++)
        {
            if (pthread_create(&threads[index], /*attr*/ NULL, run, (void *)index) != EXIT_SUCCESS)
            {
                fprintf(stderr, "Could not create a secondary thread %zu\n", index);
                return EXIT_FAILURE;
            }
        }

        printf("Hello from the main thread\n");

        for (size_t index = 0; index < thread_count; ++index)
        {
            pthread_join(threads[index], /*attr*/ NULL);
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

void *run(void *data)
{
    printf("Hello from the secondary thread %zu!\n", (size_t)data);
    return NULL;
}