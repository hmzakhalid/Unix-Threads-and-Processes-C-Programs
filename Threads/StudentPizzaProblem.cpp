#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#define THREADS 4
using namespace std;

pthread_mutex_t mutex;
int slices = 0;
int stud = 0;

void* pizzaDelivery(void* args){
    cout << "Pizza Delivered" << endl;
    slices = 8;
    return NULL;
}

void* student(void* args){
    pthread_mutex_lock(&mutex);
    int eatSlice = *(int *)args;
    int i = 1;
    stud++;
    while(eatSlice!=0){
        if(slices > 0){
            slices--;
            eatSlice--;
            cout << "Student " << stud << " ate " << i << " slice" << endl;
        }else{
            cout << "Pizza Finished, Ordering new Pizza" << endl;
            //pthread_mutex_unlock(&mutex);
            pthread_t th2;
            pthread_create(&th2, NULL, &pizzaDelivery, NULL);
            pthread_join(th2, NULL);
            sleep(1);
            //pthread_mutex_lock(&mutex);
        }
    }
    pthread_mutex_unlock(&mutex);
    cout << "Slices Left: " << slices <<endl; 
    return NULL;
}

int main(){
    srand(time(NULL));
    cout << "Number of Students: " << THREADS << "\nAll Students will eat a Random number of slices" << endl;
    slices = 8;
    pthread_t th[THREADS];
    for (int i = 0; i < THREADS; i++)
    {
        int *a = new int;
        *a = rand()%8;
        pthread_create(th + i, NULL, &student, a);
    }
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(th[i], NULL);
    }

    return 0;
}

/*A group of students are studying for a OS exam.  
The students can study only while eating pizza.  
Each student executes the following loop:
while (true)
{
    pick up a piece of pizza;
    study while eating the pizza
}
If a student finds that the pizza is gone, 
the student goes to sleep until another pizza arrives.
The first student to discover that the group is out of pizza phones Pizza Place
to order another pizza before going to sleep.
Each pizza hasS slices.Write code to synchronize
the student threads and the pizza delivery thread.
Your solution should avoid deadlock and phone
Satisfactions(i.e., wake up the delivery thread) exactly once each time a pizza is exhausted.
No piece of pizza may be consumed by more than one student.
*/