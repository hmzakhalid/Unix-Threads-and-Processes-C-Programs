#include<iostream>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

int main(){
    if(mkfifo("student", 0777) == -1){
        if(errno != EEXIST){
            cout << "Student FIFO Creation Failed" << endl;
            return 1;
        }
    }
    bool flag = true;
    while (true)
    {
        if(flag){
            char send[100];
            cout << "You: ";
            cin.getline(send, 100);
            int Write = open("student", O_WRONLY);
            //int Read = open("teacher", O_RDONLY);
            if(Write == -1) return 2;
            //if(Read == -1) return 3;
            if (write(Write, &send, sizeof(char)*100) == -1) return 4;
            close(Write);
            //close(Read);
            flag = false;
        }else{
            int Read = open("student", O_RDONLY);
            //if(Write == -1) return 2;
            if(Read == -1) return 3;
            char data[100];
            cout << "Teacher: ";
            if (read(Read, &data, sizeof(char)*100) == -1) return 4;
            cout << data << endl;
            //close(Write);
            close(Read);
            flag = true;
        }
    }
    
    return 0;
}