#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main()
{

    pid_t pid;

    int fd[2];
    pipe(fd);
    pid = fork();

    if (pid == 0)
    {

        pid_t pid2 = fork();
        if (pid2 == 0)
        {
            close(fd[0]);
            dup2(fd[1], 1);
            close(fd[1]);

            int f1 = open("input.txt", O_CREAT | O_RDONLY, 0777);
            dup2(f1, 0);
            close(f1);
            execlp("cat", "cat", NULL);
        }
        else if (pid2 > 0)
        {
            pid_t pid3 = fork();
            if (pid3 == 0)
            {
                close(fd[1]); //write end close
                dup2(fd[0], 0);
                close(fd[0]);
                int f2 = open("output.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
                dup2(f2, 1);
                close(f2);
                execlp("sort", "sort", NULL);
            }
            else
            {
                wait(NULL);
                close(fd[1]); //write end close
                dup2(fd[0], 0);
                close(fd[0]);
                int f2 = open("output.txt", O_CREAT | O_WRONLY | O_APPEND, 0777);
                dup2(f2, 1);
                close(f2);
                execlp("wc", "wc", NULL);
            }
            close(fd[1]);
            close(fd[0]);
            wait(NULL);
        }
    }
    else if (pid > 0)
    {
        return 0;
    }
}