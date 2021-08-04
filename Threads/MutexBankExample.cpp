#include <iostream>
#include <pthread.h>
#define THREADS 4
using namespace std;

pthread_mutex_t mutex[2];
int bank[] = {50, 200};

void *Withdraw(void *args)
{
    int withdraw = *(int *)args;
    pthread_mutex_lock(&mutex[0]);
    
    if (withdraw < bank[0])
    {
        bank[0] -= withdraw;
    }
    else
    {
        cout << "Not enough Balance!" << endl;
    }
    cout << "Balance is: " << bank[0] << endl;
    pthread_mutex_unlock(&mutex[0]);
    return NULL;
}

void *Deposit(void *args)
{
    int deposit = *(int *)args;
    pthread_mutex_lock(&mutex[0]);
    if (deposit > 0)
    {
        bank[0] += deposit;
    }else{
        cout << "Invalid Amount" << endl;
    }
    cout << "Balance is: " << bank[0] << endl;
    pthread_mutex_unlock(&mutex[0]);
    return NULL;
}
void *Withdraw2(void *args)
{
    int withdraw = *(int *)args;
    pthread_mutex_lock(&mutex[1]);
    if (withdraw < bank[1])
    {
        bank[1] -= withdraw;
    }
    else
    {
        cout << "Not enough Balance!" << endl;
    }
    cout << "Balance is: " << bank[1] << endl;
    pthread_mutex_unlock(&mutex[1]);
    return NULL;
}

void *Deposit2(void *args)
{
    int deposit = *(int *)args;
    pthread_mutex_lock(&mutex[1]);
    if (deposit > 0)
    {
        bank[1] += deposit;
    }
    else
    {
        cout << "Invalid Amount" << endl;
    }
    cout << "Balance is: " << bank[1] << endl;
    pthread_mutex_unlock(&mutex[1]);
    return NULL;
}

int main()
{
    pthread_mutex_init(&mutex[0], NULL);
    pthread_mutex_init(&mutex[1], NULL);
    int a=1, b, input;
    while (a != 1 || a != 2)
    {
        pthread_t th;
        cout << "1. Deposite Amount" << endl;
        cout << "2. Withdraw Amount" << endl;
        cout << "Your Choice: ";
        cin >> a;
        cout << "Chose Account (1 or 2): ";
        cin >> b;
        switch (b)
        {
        case 1:
            switch (a)
            {
            case 1:
                cout << "Enter deposit Amount: " << endl;
                cin >> input;
                pthread_create(&th, NULL, &Deposit, &input);
                pthread_join(th, NULL);
                break;
            case 2:
                cout << "Enter Withdraw Amount: " << endl;
                cin >> input;
                pthread_create(&th, NULL, &Withdraw, &input);
                pthread_join(th, NULL);
                break;
            default:
                cout << "Invalid Choice" << endl;
                return 0;
            }
            break;
        case 2:
            switch (a)
            {
            case 1:
                cout << "Enter deposit Amount: " << endl;
                cin >> input;
                pthread_create(&th, NULL, &Deposit2, &input);
                pthread_join(th, NULL);
                break;
            case 2:
                cout << "Enter Withdraw Amount: " << endl;
                cin >> input;
                pthread_create(&th, NULL, &Withdraw2, &input);
                pthread_join(th, NULL);
                break;
            default:
                cout << "Invalid Choice" << endl;
                return 0;
            }
            break;
            break;

        default:
            break;
        }
    }
    pthread_mutex_destroy(&mutex[0]);
    pthread_mutex_destroy(&mutex[1]);
    return 0;
}