#include<iostream>
#include<unistd.h>
#include<time.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

using namespace std;

int cLetters(char arr[]){
    int i=0;
    while(arr[i] != '\0'){
        i++;
    }
    return i-1;
}

int cWords(char arr[]){
    int i=0, c=0;
    while(arr[i] != '\0'){
        i++;
        if(arr[i] == ' '){
            c++;
        }
    }
    return c+1;
}

int cLines(char arr[]){
    int i=0, c=0;
    while(arr[i] != '\0'){
        i++;
        if(arr[i] == '\n'){
            c++;
        }
    }
    return c+1;
}

int main(){

    int fd = open("f2", O_RDONLY);
    if(fd == -1) return 1;
    char retrive[100];
    if( read(fd, &retrive, sizeof(char)*100) == -1) return 3;
    close(fd);
    int arr[3];
    arr[0] = cLetters(retrive);
    arr[1] = cWords(retrive);
    arr[2] = cLines(retrive);
    fd = open("f2", O_WRONLY);
    if(fd == -1) return 1;
    if( write(fd, &arr, sizeof(int)*4) == -1) return 3;
    close(fd);
    return 0;
}