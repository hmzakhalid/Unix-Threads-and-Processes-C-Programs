#include <iostream>
#include <pthread.h>
#include <string>
#include <fstream>
using namespace std;

void * countChars(void * args){
    char *name = (char *) args;
    int c = 0;
    ifstream myfile(name);
    string line;
    while(getline(myfile, line)){
        c += line.length();
    }
    myfile.close();
    cout << "Characters in " << name << " :" << c << endl;
    return NULL;
}

int main(int argc, char *argv[]){
    
    pthread_t th[2];

    for (int i = 0; i < 2; i++)
    {
        pthread_create(th + i, NULL, &countChars, argv[i+1]);
    }
    for (int i = 0; i < 2; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            cout << "Join Failed" << endl;
        };
    }

    return 0;
}