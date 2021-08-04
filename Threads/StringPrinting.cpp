#include<iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;

void* th1(void *s){
    string *g = (string *)s;
    cout << *g << endl;
}
void* th2(void *s){
    string *g = (string *)s;
    cout << *g << endl;
}

int main(){
    string s1, s2;
    cout << "Enter String 1: " << endl;
    cin >> s1;
    cout << "Enter String 2: " << endl;
    cin >> s2;
    pthread_t th[2];
    pthread_create(&th[0], NULL, &th1, &s1);
    pthread_create(&th[1], NULL, &th2, &s2);
    pthread_join(th[0], NULL);
    pthread_join(th[1], NULL);

    return 0;
}