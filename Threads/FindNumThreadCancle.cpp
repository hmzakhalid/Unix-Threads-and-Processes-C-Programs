#include<iostream>
#include <pthread.h>
#include<time.h>
using namespace std;

pthread_t th[5];
int arr[100];
void *FindNum(void *args){
    int a = *(int *)args;
    cout << a << endl;
    for(int i=a; i<a+20;i++){
        if(arr[i] == 25){
            cout << "Found at "  << i << "\nCanceling all threads"<< endl;
            for(int i=0;i<5;i++)
                pthread_cancel(th[i]);
            break;
        }
    }
    return NULL;
}

int main(){
    srand(time(NULL));
    for(int i =0; i<100; i++){
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < 5; i++)
    {
        int *a = new int;
        *a = 20*i;
        pthread_create(th + i, NULL, &FindNum, a);
    }
    for (int i = 0; i < 5; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            cout << "Join Failed" << endl;
        };
    }

    return 0;
}