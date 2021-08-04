#include<iostream>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

int main(){

    int arr[5], sum = 0;
    srand(time(NULL));
    int fd = open("sum", O_RDONLY);
    if(fd == -1) return 1;
    for(int i=0; i<5; i++){
        arr[i] = rand()%10;
        if( read(fd, &arr[i], sizeof(arr[i])) == -1) return 2;
        cout << "Read " << arr[i] << endl;
        sum += arr[i];
    }
    close(fd);
    fd = open("sum", O_WRONLY);
    if(fd == -1) return 1;
    if( write(fd, &sum, sizeof(sum)) == -1) return 3;
    close(fd);
    return 0;
}