#include <iostream>
#include <time.h>
#include <pthread.h>
using namespace std;

int **a, **b, **res;

void* Mult(void* args){
    int *arr= (int *)args;
    int r = arr[0];
    int c = arr[1];
    int l = arr[2];
    int sum = 0;
    for(int i=0; i<l; i++){
        sum += a[r][i] * b[i][c];
    }
    delete[]arr;
    int *sumSend = new int;
    *sumSend = sum;
    return (void*)sumSend;
}

int main()
{
    srand(time(NULL));
    int r1, c1, r2, c2;
    int mult[10][10];

    cout
        << "Enter rows and columns for first matrix" << endl;
    cout << "Row: ";
    cin >> r1;
    cout << "Column: ";
    cin >> c1;
    cout << "Enter rows and columns for second matrix" << endl;
    cout << "Row: ";
    cin >> r2;
    cout << "Column: ";
    cin >> c2;

    while (c1 != r2)
    {
        cout << "Error! column of first matrix MUST match row of second." << endl;
        cout << "Enter rows and columns for first matrix: " << endl;
        cout << "Row: ";
        cin >> r1;
        cout << "Column: ";
        cin >> c1;

        cout << "Enter rows and columns for second matrix: " << endl;
        cout << "Row: ";
        cin >> r2;
        cout << "Column: ";
        cin >> c2;
    }
    a = new int *[r1];
    b = new int *[r2];
    res = new int *[r1];
    for (int i = 0; i < r1; ++i)
        a[i] = new int[c1];
    for (int i = 0; i < r2; ++i)
        b[i] = new int[c2];
    for (int i = 0; i < r1; ++i)
        res[i] = new int[c2];

    cout << endl
         << "Enter elements of matrix 1:" << endl;
    for (int i = 0; i < r1; ++i)
    {
        for (int j = 0; j < c1; ++j)
        {
            cout << "Enter element a" << i + 1 << j + 1 << " : ";
            cin >> a[i][j];
        }
        cout << endl;
    }

    cout << endl
         << "Enter elements of matrix 2:" << endl;
    for (int i = 0; i < r2; ++i)
    {
        for (int j = 0; j < c2; ++j)
        {
            cout << "Enter element b" << i + 1 << j + 1 << " : ";
            cin >> b[i][j];
        }
        cout << endl;
    }
    cout << endl;
    int resNum = r1*c2;
    pthread_t *th = new pthread_t[resNum];
    int k = 0;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            int *arr = new int[3];
            arr[0] = i;
            arr[1] = j;
            arr[2] = c1;
            pthread_create(th+k, NULL, &Mult, arr);
            k++;
        }
    }
    k=0;
    for (int i = 0; i < r1; i++)
    {
        for(int j=0; j<c2; j++){
            int *temp;
            pthread_join(th[k], (void **)&temp);
            res[i][j] = *temp;
            delete temp;
            k++;
        }
    }
   
    cout << endl
         << "Output Matrix: " << endl;
    for (int i = 0; i < r1; i++)
    {
        for (int j = 0; j < c2; j++)
        {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    

    return 0;
}