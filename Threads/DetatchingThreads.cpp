#include <iostream>
#include <pthread.h>
using namespace std;


void *routine(void *arg)
{
    cout << "Finished Thread Execute" << endl;
    return NULL;
}

int main()
{
    pthread_t th[5];

    for (int i = 0; i < 5; i++)
    {
        pthread_create(th + i, NULL, &routine, NULL);
        pthread_detach(th[i]);

    }
    for (int i = 0; i < 5; i++)
    {
        if( pthread_join(th[i], NULL) != 0){
            cout << "Join Failed" << endl;
        }; 
    }
    

    pthread_exit(0);
}