#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t semaphore;

void* print_thread_id(void* arg);

int main() {
    int N = sysconf(_SC_NPROCESSORS_ONLN);
    int MAX_CONCURRENT = N;

    sem_init(&semaphore, 0, MAX_CONCURRENT);

    pthread_t threads[N];
    for (int i = 0; i < N; i++) {
        pthread_create(&threads[i], NULL, print_thread_id, NULL);
    }
    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Fim\n");
    sem_destroy(&semaphore);
    return 0;
}

void* print_thread_id(void* arg) {
    sem_wait(&semaphore);
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    sem_post(&semaphore);
    return NULL;
}
