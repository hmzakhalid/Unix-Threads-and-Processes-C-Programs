#include<iostream>
#include<unistd.h>
#include<pthread.h>


using namespace std;

void* hello(void *args){
    cout << "Hello" << endl;
}

int main(){
    srand(time(NULL));
    pthread_t th[5];
    for(int i=0; i<5; i++){
        pthread_create(th+i, NULL, &hello, NULL);
        cout << "Thread " << i << " started" << endl;
    }
    for(int i=0; i<5; i++){
        pthread_join(th[i], NULL);
        cout << "Thread " << i << " Stopped" << endl;
    }

    return 0;
}