#include<iostream>

using namespace std;

int main(int argc, char *argv[]){
    int find;
    cout << "Enter Element to Search: ";
    cin >> find;
    int arr[10];
    for(int i=0; i<10; i++){
        arr[i] = atoi(argv[i]);
        cout << arr[i] << " ";
    }

}