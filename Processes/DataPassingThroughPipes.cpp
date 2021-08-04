#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <sys/wait.h>
//#inlcude <sys /types.h>
#include <errno.h>
using namespace std;

int main()
{
    int fd[3][2];
    int i;

    for (i = 0; i < 3; i++)
    {

        if (pipe(fd[i]) < 0)
        {
            cout << "erro" << endl;
        }
    }
    pid_t id = fork();
    if (id == 0)
    {
        close(fd[0][1]);
        close(fd[1][0]);
        close(fd[2][0]);
        close(fd[2][1]);
        int x;
        cout << "Enter a Value of X: ";
        cin >> x;
        if (write(fd[1][1], &x, sizeof(int)) < 0)
        {
            return 2;
        }
        close(fd[1][1]);
        exit(0);
    }else{
        wait(NULL);
        pid_t id1 = fork();
        if (id1 == 0)
        {
            close(fd[0][0]);
            close(fd[0][1]);
            close(fd[1][1]);
            close(fd[2][0]);
            int x;
            if (read(fd[1][0], &x, sizeof(int)) < 0)
            {
                return 4;
            }
            x += 5;
            cout << x << endl;
            if (write(fd[2][1], &x, sizeof(int)) < 0)
            {
                return 5;
            }
            close(fd[1][0]);
            close(fd[2][1]);
        }
        else if(id1 != -1){
            wait(NULL);
            close(fd[0][0]);
            close(fd[1][0]);
            close(fd[1][1]);
            close(fd[2][1]);
            int x;
            read(fd[2][0], &x, sizeof(int));
            x+=3;
            cout <<"Final value: "<< x << endl;
            close(fd[2][0]);
            waitpid(id, NULL, 0);
            waitpid(id1, NULL, 0);
        }
    }
    return 0;
}
