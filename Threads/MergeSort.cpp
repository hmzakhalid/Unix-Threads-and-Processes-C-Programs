#include <iostream>
#include <pthread.h>
#include <time.h>
#include <vector>

using namespace std;

int *arr;

vector<int> splitSeq(int x, int n=4)
{
    vector<int> a;
    if (x < n)
       a.push_back(-1);
    else if (x % n == 0)
    {
        for (int i = 0; i < n; i++)
            a.push_back(x/n);
    }
    else
    {
        int zp = n - (x % n), pp = x / n;
        for (int i = 0; i < n; i++)
        {

            if (i >= zp)
                a.push_back(pp+1);
            else
                a.push_back(pp);
        }
    }
    return a;
}
int getMid(int first, int last){
    return first + (last - first) / 2;
}

void merge(int first, int mid, int last)
{
    int n1 = mid - first + 1;
    int n2 = last - mid;

    int L[n1], M[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[first + i];
    for (int j = 0; j < n2; j++)
        M[j] = arr[mid + 1 + j];

 
    int i, j, k;
    i = 0;
    j = 0;
    k = first;


    while (i < n1 && j < n2)
    {
        if (L[i] <= M[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = M[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = M[j];
        j++;
        k++;
    }
}
void mergeSort(int first, int last)
{
    if (first < last)
    {
        int mid = getMid(first, last);

        mergeSort(first, mid);
        mergeSort(mid + 1, last);
        merge(first, mid, last);
    }
}

void *mergeCall(void *args){
    int *Link = (int*)args;
    mergeSort(Link[0], Link[1]-1);
    delete [] Link;
    return NULL;
}

int main(){
    srand(time(NULL));
    int cores = 4;
    cout << "Number of Cores: "<< cores << endl
         << "MAC : 70-C9-4E-75-93-47" << endl;
    int arrSize;
    cout << "Enter Size of Array: ";
    cin >> arrSize;
    if(arrSize < cores){
        cores = arrSize;
    }
    arr = new int[arrSize];
    for(int i = 0; i < arrSize; i++){
        cout << "Enter Value " << i+1 << ": ";
        cin>> arr[i];
    }
    cout << "Unsorted Array:" << endl;
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << " ";
    }
    vector<int> a = splitSeq(arrSize);
    int b=0;
    pthread_t th[cores];
    for (int i = 0; i < cores; i++)
    {
        int *Link = new int[2];
        Link[0] = b;
        Link[1] = b+a[i];
        b = Link[1];
        pthread_create(th + i, NULL, &mergeCall, Link);
    }
    cout << endl << endl;
    b=0;
    for (int i = 0; i < cores; i++)
    {
        pthread_join(th[i], NULL);
        
    }

    for(int i=0; i<cores; i++){
        a[i+1] += a[i];
    }

    merge(0, getMid(0, a[1]) - 1, a[1] - 1);
    merge(a[1], getMid(a[1], a[3])-1, a[3] - 1);
    merge(0, a[1]-1, a[3] - 1);
    cout << "Sorted Array: " << endl;
    for (int i = 0; i < arrSize; i++)
    {
        cout << arr[i] << " ";
    }
}