#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;

void* evenOdd(void *a){
    int *c = (int *)a;
    if(*c %2 == 0){
        cout << "Number is Even" << endl;
    }else{
        cout << "Number is Odd" << endl;
    }
}

int main(){
    int a;
    cout << "Enter a Number: ";
    cin >> a;
    pthread_t th;
    pthread_create(&th, NULL, &evenOdd, &a);
    pthread_join(th, NULL);


    return 0;
}