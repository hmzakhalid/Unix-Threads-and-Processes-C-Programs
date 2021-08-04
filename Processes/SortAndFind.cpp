#include <iostream>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
#include <sys/wait.h>
using namespace std;

int main(int argc, char *argv[]){
    srand(time(NULL));
    vector<int> arr(10);
    char *charArr[10];
    cout << "Before Sorting!" << endl;
    for(int i=0; i<10; i++){
        arr[i] = rand()%20;
        cout << arr[i] << " ";
    }
    cout << endl;
    sort(arr.begin(), arr.end());
    cout << "After Sorting!" << endl;
    string s;
    for(int i=0; i<10; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
    pid_t id=fork();
    if(id==0)
    {
        execv("./child", charArr);
        perror("Error in execve call...");
    }
}