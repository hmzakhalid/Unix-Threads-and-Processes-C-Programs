#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main()
{
    cout << "PID Before Fork: " << getpid() << endl;
    int file = open("write.txt", O_WRONLY | O_RDONLY | O_CREAT, 0777);

    pid_t id = fork();
    if (id == -1)return 1;
    if (id == 0)
    {
        dup2(file, 1);
        cout << "Child PID: " << getpid() << endl;
        dup2(STDIN_FILENO, 1);
        cout << "Child: All Done" << endl;
    }
    else
    {
        wait(NULL);
        cout << "Parent PID: " << getpid() << endl;
        cout << "Parent: All Done" << endl;

    }
    return 0;
}