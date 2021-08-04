#include<iostream>
#include <unistd.h>
#include<pthread.h>
using namespace std;

int balance = 1000;
bool successful = false;

void *Withdraw(void *args){
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int withdraw = *(int*)args;
    if(withdraw < balance){
        balance -= withdraw;
        successful = true;
    }else{
        cout << "Not enough Balance!" << endl;
        successful = false;

    }
    pthread_cancel(pthread_self()); // 
    sleep(2); // Just to demonstrate that the thread is being cancelled, Otherwise it would sleep
    return NULL;
}

void *Deposit(void *args)
{
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    int deposit = *(int *)args;
    if (deposit > 0)
    {
        balance += deposit;
        successful = true;
    }
    else
    {
        successful = false;
    }
    pthread_cancel(pthread_self()); //
    return NULL;
}

int main(){
    int a, input;
    while(a != 1 || a!=2 || a!=3){
        pthread_t th;
        cout << "\n1. Check Account Balance" << endl;
        cout << "2. Deposite Amount" << endl;
        cout << "3. Withdraw Amount" << endl;
        cout << "Your Choice: ";
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "Account Balance: " << balance << endl;
            break;
        case 2:
            cout << "Enter deposit Amount: " << endl;
            cin >> input;
            pthread_create(&th, NULL, &Deposit, &input);
            break;
        case 3:
            cout << "Enter Withdraw Amount: " << endl;
            cin >> input;
            pthread_create(&th, NULL, &Withdraw, &input);
            break;
        default:
            cout << "Invalid Choice" << endl;
            return 0;
        }
    }
    

    return 0;
}