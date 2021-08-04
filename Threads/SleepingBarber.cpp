#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

using namespace std;
int chairs[5], counter =0;
pthread_mutex_t mutex;
sem_t emptyChair, barberChair;
int input;

void* customer(void* args){
    int a = *(int*)args;
    for(int i=0; i<a; i++){
        sem_wait(&emptyChair);
        pthread_mutex_lock(&mutex);
        chairs[counter] = i;
        cout << "New Customer: " << i << endl;
        counter++;
        pthread_mutex_unlock(&mutex);
        sem_post(&barberChair);
    }
    return NULL;
}

void *barber(void *args)
{
    int a = *(int *)args;
    for(int i=0; i<a; i++){
        sem_wait(&barberChair);
        pthread_mutex_lock(&mutex);
        cout << "Barber Cut Hair of " << chairs[counter-1] << endl;
        cout << "Customer " << chairs[counter-1] << " leaves the shop." << endl;
        counter--;
        pthread_mutex_unlock(&mutex);
        sem_post(&emptyChair);
        sleep(1);
        
    }
    cout << "All Customers are Gone. Barber went home" << endl;

    return NULL;
}

int main()
{
    cout << "Enter Number of Customers(greater than 5): ";
    cin >> input;
    srand(time(NULL));
    sem_init(&emptyChair, 0, 5);
    sem_init(&barberChair, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_t th[2];
    for (int i = 0; i < 2; i++)
    {
        if(i%2==0){
            pthread_create(th + i, NULL, &customer, &input);
        }else{
            pthread_create(th + i, NULL, &barber, &input);
        }
    }
    for (int i = 0; i < 2; i++)
    {
        pthread_join(th[i], NULL);
    }
    sem_destroy(&emptyChair);
    sem_destroy(&barberChair);
    pthread_mutex_destroy(&mutex);
    return 0;
}