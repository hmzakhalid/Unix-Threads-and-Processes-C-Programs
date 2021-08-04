#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

using namespace std;

int main(){
    char arr[5];
    cout << "Enter a 5 Letter name: ";
    cin >> arr;
    pid_t id = fork();
    if(id > 0){
        wait(NULL);
        cout << arr[4];
    }else if(id == 0){
        pid_t id2 = fork();
        if(id2 > 0){
            wait(NULL);
            cout << arr[3];
        }else if(id == 0){
            pid_t id3 = fork();
            if(id3 > 0){
                wait(NULL);
                cout << arr[1];
            }else if( id3 == 0){
                cout << arr[0];
                exit(0);
            }
            cout << arr[2];
            exit(0);
        }
        exit(0);
    }
    cout << endl;
}