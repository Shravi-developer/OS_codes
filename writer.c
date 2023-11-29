#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t canRead = PTHREAD_COND_INITIALIZER;
pthread_cond_t canWrite = PTHREAD_COND_INITIALIZER;

int sharedData = 0;
int readersCount = 0;

void *reader(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        readersCount++;

        // If a writer is writing, or if it's the first reader, wait
        while (sharedData == -1) {
            pthread_cond_wait(&canRead, &mutex);
        }

        printf("Reader %d read: %d\n", *((int *)arg), sharedData);

        readersCount--;

        // If it's the last reader, signal the writer to write
        if (readersCount == 0) {
            pthread_cond_signal(&canWrite);
        }

        pthread_mutex_unlock(&mutex);

        // Simulate some processing time
        usleep(rand() % 1000000);
    }

    return NULL;
}

void *writer(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // If a reader is reading or a writer is writing, wait
        while (readersCount > 0 || sharedData == -1) {
            pthread_cond_wait(&canWrite, &mutex);
        }

        sharedData = rand() % 100;
        printf("Writer wrote: %d\n", sharedData);

        // Signal readers that they can read
        pthread_cond_broadcast(&canRead);

        pthread_mutex_unlock(&mutex);

        // Simulate some processing time
        usleep(rand() % 1000000);
    }

    return NULL;
}

int main() {
    pthread_t readers[3], writers[2];
    int readerIDs[3] = {1, 2, 3};
    int writerIDs[2] = {1, 2};

    // Create reader threads
    for (int i = 0; i < 3; ++i) {
        pthread_create(&readers[i], NULL, reader, &readerIDs[i]);
    }

    // Create writer threads
    for (int i = 0; i < 2; ++i) {
        pthread_create(&writers[i], NULL, writer, &writerIDs[i]);
    }

    // Let the threads run for a while
    sleep(5);

    // Exit the threads
    for (int i = 0; i < 3; ++i) {
        pthread_cancel(readers[i]);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_cancel(writers[i]);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&canRead);
    pthread_cond_destroy(&canWrite);

    return 0;
}
