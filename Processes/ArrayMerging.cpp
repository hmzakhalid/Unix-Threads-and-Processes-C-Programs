#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
using namespace std;

int tell_size(char arr[]){
    int i= 0;
    while(arr[i] != '\0'){
        i++;
    }
    return i;
}

int main(){
    int fd[2],TotalSum;
    if(pipe(fd) == -1){
        cout << "Error in Creating Pipe\n";
        return 1;
    }
    pid_t id=fork();
    if(id==0){
        wait(NULL);
        char P2String[20] = "String 2 ";
        cout << "Process 2: " << P2String << endl;
        char P1String[20];
        read(fd[0], &P1String, sizeof(P1String));
        close(fd[0]);
        int size1 = tell_size(P1String);
        int size2= tell_size(P2String);
        char *final = new char[size1+size2];
        int j = 0;
        for(int i=0; i<size1; i++){
            final[j] = P1String[i];
            j++;
        }
        for(int i=0; i<size2; i++){
            final[j] = P2String[i];
            j++;
        }
        write(fd[1], final, sizeof(char)*100);
        close(fd[1]);

    }else if(id != -1){
        char arr[20] = "String 1 ";
        cout << "Process 1: " << arr << endl;
        write(fd[1], &arr, sizeof(arr));
        close(fd[1]);
        wait(NULL);
        char *final = new char[100];
        read(fd[0], final, sizeof(char)*100);
        close(fd[0]);
        cout << "Final Array is: "<< final << endl; 
    }

}