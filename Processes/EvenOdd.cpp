#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    int arr[10];
    cout << "Enter 10 Numbers: ";
    for(int i=0; i<10; i++){
        cin >> arr[i];
    }
    pid_t id = fork();
    if(id > 0){
        wait(NULL);
        cout << "Odd in Parent: ";
        for(int i=0; i<10; i++){
            if(arr[i]%2 == 1)
                cout << arr[i] << " ";
        }
        cout << endl;
    }else if( id == 0 ){
        cout << "Even in Child: ";
        for(int i=0; i<10; i++){
            if(arr[i]%2 == 0)
                cout << arr[i] << " ";
        }
        cout << endl;
        exit(0);
    }
    
}