#include <iostream>
#include <pthread.h>

using namespace std;

struct SumArray{
    int *arr1;
    int *arr2;
    int size;
    int *result;
};

void * sumArray(void * args){
    SumArray temp = *(SumArray *) args;
    temp.result = new int[temp.size];
    cout << "Sum of the Elements are: " << endl;
    for(int i=0; i<temp.size; i++){
        temp.result[i] = temp.arr1[i] + temp.arr2[i];
        cout << temp.result[i] << " ";
    }
    cout << endl;
    return NULL;
}


int main(int argc, char *argv[]){
    SumArray obj;
    int temp = stoi(argv[1]);
    obj.size = temp;
    obj.arr1 = new int[temp];
    obj.arr2 = new int[temp];
    cout << "Enter Value in Array 1" << endl;
    for(int i=0; i<temp; i++){
        cout << "Value " << i << ": ";
        cin >> obj.arr1[i];
    }
    cout << "\nEnter Value in Array 2" << endl;
    for (int i = 0; i < temp; i++)
    {
        cout << "Value " << i << ": ";
        cin >> obj.arr2[i];
    }
    cout << endl;
    pthread_t th;
    pthread_create(&th, NULL, &sumArray, &obj);
    pthread_join(th, NULL);
    return 0;
}