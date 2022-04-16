#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    size_t thread_count;
} shared_data_t;

typedef struct
{
    size_t thread_number;
    shared_data_t *shared_data
} private_data_t;

int create_threads(shared_data_t *shared_data);
void *run(void *data);

int main(int argc, char *argv[])
{
    int error = EXIT_SUCCESS;

    shared_data_t *shared_data = (shared_data_t *)calloc(1, sizeof(shared_data_t));

    if (shared_data)
    {
        shared_data->thread_count = sysconf(_SC_NPROCESSORS_ONLN);

        if (argc == 2)
        {
            if (sscanf(argv[1], "%zu", &shared_data->thread_count) != 1 || errno)
            {
                fprintf(stderr, "error: invalid thread count!\n");
                return EXIT_FAILURE;
            }
        }

        error = create_threads(shared_data);
        free(shared_data);
    }

    return error;
}

int create_threads(shared_data_t *shared_data)
{
    assert(shared_data); 
    
    int error = EXIT_SUCCESS;
    pthread_t *threads = (pthread_t *)calloc(shared_data->thread_count, sizeof(pthread_t));

    private_data_t *private_data = (private_data_t *)calloc(shared_data->thread_count, sizeof(private_data_t));

    if (threads && private_data)
    {
        for (size_t index = 0; index < shared_data->thread_count; index++)
        {
            private_data[index].thread_number = index;
            private_data[index].shared_data = shared_data;

            if (pthread_create(&threads[index], /*attr*/ NULL, run, (void *)index) != EXIT_SUCCESS)
            {
                fprintf(stderr, "Could not create a secondary thread %zu\n", index);
                error = 21;
                break;
            }
        }

        printf("Hello from the main thread\n");

        for (size_t index = 0; index < shared_data->thread_count; ++index)
        {
            pthread_join(threads[index], /*attr*/ NULL);
        }

        free(threads);
        free(private_data);
    }
    else
    {
        fprintf(stderr, "Could not allocate memory for %zu threads\n", shared_data->thread_count);
        error = 22;
    }

    return error;
}

void *run(void *data)
{
    const private_data_t *private_data = (private_data_t *)data;
    printf("Hello from the secondary thread %zu of %zu\n", private_data->thread_number, private_data->shared_data->thread_count);
    return NULL;
}