#include<iostream>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

int main(){
    if (mkfifo("f2", 0777) == -1){
        if(errno != EEXIST){
            cout << "File Creation Failed" << endl;
            return 1;
        }
    }
    char data[100];
    cout << "Enter Data(0 to exit):\n";
    int i=0;
    while(cin >> data[i]){
        if(data[i] == '0')
        break;
        i++;
    }
    int fd = open("f2", O_WRONLY);
    if(fd == -1) return 1;
    if( write(fd, &data, sizeof(char)*100) == -1) return 2;
    close(fd);
    int arr[3];
    fd = open("f2", O_RDONLY);
    if(fd == -1) return 1;
    if( read(fd, &arr, sizeof(int)*4) == -1) return 3;
    cout << "Letter Count: " << arr[0] << endl;
    cout << "Word Count: " << arr[1] << endl;
    cout << "Line Count: " << arr[2] << endl;
    close(fd);
    return 0;
}