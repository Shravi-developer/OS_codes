#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
sem_t empty, full;
pthread_mutex_t mutex;

void init() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL); 
}

void *producer(void *arg) {
    int item;
    for (int i = 0; i < 5; i++) {
        item = rand() % 10; 
        sem_wait(&empty); 
        pthread_mutex_lock(&mutex); 
        buffer[i % BUFFER_SIZE] = item; 
        printf("Producer produced item %d\n", item);
        pthread_mutex_unlock(&mutex); 
        sem_post(&full); 
        sleep(1); 
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < 5; i++) {
        sem_wait(&full); 
        pthread_mutex_lock(&mutex); 
        item = buffer[i % BUFFER_SIZE]; 
        printf("Consumer consumed item %d\n", item);
        pthread_mutex_unlock(&mutex); 
        sem_post(&empty); 
        sleep(2); 
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    init(); 
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
