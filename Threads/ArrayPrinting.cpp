#include<iostream>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

using namespace std;

void* th1(void *s){
    int *a = (int *)s;
    for(int i=0; i<5; i++){
        cout << a[i] << endl;
    }
}
void* th2(void *s){
    
    int *a = (int *)s;
    for(int i=5; i<10; i++){
        cout << a[i] << endl;
    }
}

int main(){
    srand(time(NULL));
    int arr[10];
    for(int i=0; i<10; i++){
        arr[i] = rand()%10;
    }
    pthread_t th[2];
    pthread_create(&th[0], NULL, &th1, arr);
    pthread_create(&th[1], NULL, &th2, arr);
    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    return 0;
}