#include <iostream>
#include <queue>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
using namespace std;

#define BUFFER_SIZE 5

queue<int> buffer;
sem_t emptySlots, fullSlots, mutexLock;

void* producer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&emptySlots);   // wait for empty slot
        sem_wait(&mutexLock);    // enter critical section

        buffer.push(i);
        cout << "Produced: " << i << endl;

        sem_post(&mutexLock);    // leave critical section
        sem_post(&fullSlots);    // signal item produced
        sleep(1);
    }
    pthread_exit(NULL);
}

void* consumer(void* arg) {
    for (int i = 1; i <= 5; i++) {
        sem_wait(&fullSlots);    // wait for available item
        sem_wait(&mutexLock);    // enter critical section

        int item = buffer.front();
        buffer.pop();
        cout << "Consumed: " << item << endl;

        sem_post(&mutexLock);    // leave critical section
        sem_post(&emptySlots);   // signal space available
        sleep(2);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t prodThread, consThread;

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    sem_init(&mutexLock, 0, 1);

    pthread_create(&prodThread, NULL, producer, NULL);
    pthread_create(&consThread, NULL, consumer, NULL);

    pthread_join(prodThread, NULL);
    pthread_join(consThread, NULL);

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    sem_destroy(&mutexLock);

    return 0;
}
