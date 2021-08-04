#include<iostream>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<unistd.h>

int buffer[10];
int in = 0, out = 0;
sem_t s;
sem_t full, empty;

void *producer(void *args){

    while (1)
    {
        sem_wait(&empty);
        sem_wait(&s);
        //Critical Section
        buffer[in] = rand() % 10 + 1;
        std::cout << "Produced: " << buffer[in] << std::endl;
        in = (in + 1) % 10;
        sem_post(&s);
        sem_post(&full);
    }
    
    
    return NULL;
}

void *consumer(void *args)
{
    while (1)
    {
        sem_wait(&full);
        sem_wait(&s);
        // Critical Section
        std::cout << "Consumed: " << buffer[out] << std::endl;
        out = (out +1 ) %10;
        sem_post(&s);
        sem_post(&empty);
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    sem_init(&s, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    pthread_t th[2];
    pthread_create(&th[0], NULL, &producer, NULL);
    pthread_create(&th[1], NULL, &consumer, NULL);
    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);
    sem_destroy(&s);
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0;
}