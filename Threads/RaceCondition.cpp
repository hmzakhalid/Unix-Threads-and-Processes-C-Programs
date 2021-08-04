#include <iostream>
#include <pthread.h>
#define THREADS 2
using namespace std;


int countGold = 0;

void *routine(void *args)
{
    for(int i=0; i<1000000;i++){
        countGold++;
    }
    return NULL;
}


int main()
{
    pthread_t th[THREADS];
    for (int i = 0; i < THREADS; i++)
    {
        pthread_create(th + i, NULL, &routine, NULL);
    }
    for (int i = 0; i < THREADS; i++)
    {
        pthread_join(th[i], NULL);
    }
    cout << countGold << endl;
    cout << "The Output is Wrong because\nExample: Gold Value is 50 in Current state " << endl 
    << "Thread 1 Reads the Value of Gold at 50 and Pauses it Execution for a while" << endl 
    << "Thread 2 Reads the Value of Gold at 50 and increments it 10 times and Writes 60 in memory" << endl
    << "Thread 1 resumes its execution and increments 50 to 51 and overwrites the 60 in memeory" << endl
    << "This is the Issue in this program" << endl;
    return 0;
}