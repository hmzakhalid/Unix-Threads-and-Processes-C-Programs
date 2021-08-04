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
    pthread_attr_t detach;
    pthread_attr_init(&detach);
    pthread_attr_setdetachstate(&detach, PTHREAD_CREATE_DETACHED);
    for (int i = 0; i < 5; i++)
    {
        
        pthread_create(th + i, &detach, &routine, NULL);

    }
    for (int i = 0; i < 5; i++)
    {
        if( pthread_join(th[i], NULL) != 0){
            cout << "Join Failed" << endl;
        }; 
    }
    
    pthread_attr_destroy(&detach);
    pthread_exit(0);
}