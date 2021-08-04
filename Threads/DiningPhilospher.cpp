#include<iostream>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>

using namespace std;

sem_t forks[5];
sem_t sem;

void* Philospher(void * args){
    int *n = (int*)args;
    int id = *n;
    delete n;
    while(true){
        cout << "Philospher " << id << " is Thinking" << endl;
        sem_wait(&sem);
        // Take Fork
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%5]);
        // Eat
        cout << "Philospher " << id << " is Eating" << endl;
        // Put Fork
        sem_post(&forks[id]);
        sem_post(&forks[(id + 1) % 5]);
        sem_post(&sem);
        sleep(1);
    }
    return NULL;
}

int main(){
    pthread_t th[5];
    sem_init(&sem, 0, 4);
    for(int i=0; i<5; i++)
        sem_init(forks+i,0,1);
    for(int i=0;i<5; i++){
        int *a = new int;
        *a = i;
        pthread_create(th+i, NULL, &Philospher, a);
    }

    for(int i = 0; i < 5; i++)
        sem_destroy(forks + i);
        sem_destroy(&sem);
    for (int i = 0; i < 5; i++)
        pthread_join(th[i], NULL);

    return 0;
}