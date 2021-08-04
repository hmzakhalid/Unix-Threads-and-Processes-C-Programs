#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(){
    char *fname = new char[100];
    cout << "Enter a Filename in the current dir or full path: ";
    cin >> fname;
    pid_t id = fork();
    if(id == 0){
        cout << "Execlp with PID: " << getpid() << endl;
        execlp("stat", "stat", "--format=\"%n\"", fname, NULL);
        cout << "Execlp Failed to Run" << endl;
    }else{
        wait(NULL);
        pid_t id2 = fork();
        if(id2 == 0){
            cout << "Execl with PID: " << getpid() << endl;
            execl("/bin/stat", "stat", "--format=\"%U\"", fname, NULL);
            cout << "Execl Failed to Run" << endl;
        }else{
            wait(NULL);
            pid_t id3 = fork();
            if(id3 == 0){
                cout << "Execvp with PID: " << getpid() << endl;
                char *args[] = {"stat", "--format=\"%x\"", fname, NULL}; 
                execvp("stat", args);
                cout << "Execvp Failed to Run" << endl;
            }else{
                wait(NULL);
                pid_t id4 = fork();
                if(id4 == 0){
                    cout << "Execv with PID: " << getpid() << endl;
                    char *args[] = {"stat", "--format=\"%z\"", fname, NULL}; 
                    execv("/bin/stat", args);
                    cout << "Execv Failed to Run" << endl;
                }else{
                    wait(NULL);
                    pid_t id5 = fork();
                    if(id5 == 0){
                        cout << "Execve with PID: " << getpid() << endl;
                        char *envp[] = {"PATH=bin:/usr/bin",NULL};
                        char *args[] = {"stat", "--format=\"%y\"",  fname, NULL}; 
                        execve("/bin/stat", args, envp);
                        cout << "Execve Failed to Run" << endl;
                    }else{
                        wait(NULL);
                        cout << "Execle with PID: " << getpid() << endl;
                        char *envp[] = {"PATH=bin:/usr/bin",NULL};
                        execle("/bin/stat", "stat",fname,NULL, envp);
                        cout << "Execle Failed to Run" << endl;
                    }
                }
            }
        }
    }

}