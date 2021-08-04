#include<iostream>
#include<unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    int arr[]={1,2,3,4,5,6};
    int fd[2],TotalSum;
    int arrsize=sizeof(arr)/sizeof(int);
    if(pipe(fd) == -1){
        cout << "Error in Creating Pipe\n";
        return 1;
    }

    pid_t id=fork();
    if(id==0){
        int sum = arr[0] + arr[1];
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
        cout<<"Child Process 1 Sum: " << sum <<endl;
    }else if(id != -1){
        wait(NULL);
        pid_t id2=fork();
        if(id2==0){
            int sum = arr[2] + arr[3];
            close(fd[0]);
            write(fd[1], &sum, sizeof(sum));
            close(fd[1]);
            cout<<"Child Process 2 Sum: " << sum <<endl;
        }else if(id2 != -1){
            wait(NULL);
            int Child1Sum,Child2Sum; 
            int  ParentSum = arr[4] + arr[5];
            cout << "Parent Sum: " << ParentSum << endl;
            close(fd[1]);
            read(fd[0], &Child1Sum, sizeof(Child1Sum));
            read(fd[0], &Child2Sum, sizeof(Child2Sum));
            close(fd[0]);
            TotalSum = ParentSum + Child1Sum +Child2Sum;
            cout << "Total Sum: " << TotalSum << endl;
        }
    }
    
}