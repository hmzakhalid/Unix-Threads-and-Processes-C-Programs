#include<iostream>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

int main(){
    if (mkfifo("sum", 0777) == -1){
        if(errno != EEXIST){
            cout << "File Creation Failed" << endl;
            return 1;
        }
    }

    int arr[5], sum;
    srand(time(NULL));
    int fd = open("sum", O_WRONLY);
    if(fd == -1) return 1;
    for(int i=0; i<5; i++){
        arr[i] = rand()%10;
        if( write(fd, &arr[i], sizeof(arr[i])) == -1) return 2;
        cout << "Wrote " << arr[i] << endl;
    }
    close(fd);
    fd = open("sum", O_RDONLY);
    if(fd == -1) return 1;
    if( read(fd, &sum, sizeof(sum)) == -1) return 3;
    cout << "Sum is " << sum << endl;
    close(fd);
    return 0;
}