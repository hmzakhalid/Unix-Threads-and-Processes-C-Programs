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
    int sum = 0;  
    int des[2];
    pipe(des);
    int a = 0, b = 0;
    pid_t id = fork();
    if(id > 0){
        wait(NULL);
        cout << "ID of Parent is: " << getpid() << endl;
        for(int i=0; i<5; i++){
            a += arr[i];
        }
        close(des[1]);
        read(des[0], &sum, sizeof(sum));
        sum += a;
    }else if( id == 0 ){
        cout << "ID of Child is: " << getpid() << endl;
        for(int i=5; i<10; i++){
            b += arr[i];
        }
        close(des[0]);
        write(des[1], &b, sizeof(b));
        exit(0);
    }

    cout << "Sum of the Array is: " << sum << endl;
    
}