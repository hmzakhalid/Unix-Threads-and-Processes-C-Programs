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
        cout << "Parent: ";
        for(int i=0; i<5; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
    }else if( id == 0 ){
        cout << "Child: ";
        for(int i=5; i<10; i++){
            cout << arr[i] << " ";
        }
        cout << endl;
        exit(0);
    }
    
}