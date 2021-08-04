/* 
A university computer science department has a teaching assistant (TA) 
who helps undergraduate students with their programming assignments 
during regular office hours. The TA’s office is rather small and 
has room for only one desk with a chair and computer. There are 
three chairs in the hallway outside the office where students can 
sit and wait if the TA is currently helping another student. When 
there are no students who need help during office hours, the TA sits 
at the desk and takes a nap. If a student arrives during office hours
and finds the TA sleeping, the student must awaken the TA to ask for help. 
If a student arrives and finds the TA currently helping another student, 
the students its on one of the chairs in the hallway and waits. 
If no chairs are available, the student will come back at a later time.
Using POSIX threads, mutex locks, and semaphores, 
implement a solution that coordinates the activities of the TA and the students. 
*/

#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

using namespace std;

int waitingChair[3];
int waitingStudents = 0;
int counter = 0;
sem_t ta_sem, student_sem;
bool isSleeping = true;
pthread_mutex_t mutex;

bool isWating(int id)
{
    for (int i = 0; i < 3; i++)
    {
        if (id == waitingChair[i])
        {
            return true;
        }
    }
    return false;
}

void *TA(void *args)
{
    while (1)
    {
        if (waitingStudents > 0)
        {
            sem_wait(&ta_sem);
            pthread_mutex_lock(&mutex);
            isSleeping = false;
            sleep(1);
            cout << "TA Helped Student " << waitingChair[waitingStudents-1] << " with his assignment" << endl;
            waitingStudents--;
            if (waitingStudents == 0)
            {
                isSleeping = true;
            }
            pthread_mutex_unlock(&mutex);
            sem_post(&student_sem);
            
        }
        else
        {
            if (isSleeping == true)
            {
                cout << "No Students Waiting!, TA Sleeps" << endl;
                isSleeping = false;
            }
        }
    }
    return NULL;
}

void *Student(void *args)
{
    int id = *(int *)args;
    while (1)
    {
        if (waitingStudents < 3)
        {
            if (isWating(id))
                continue;
            sem_wait(&student_sem);
            pthread_mutex_lock(&mutex);
            waitingChair[waitingStudents] = id;
            waitingStudents++;
            cout << "Student Number " << id << " Took a Seat!" << endl;
            pthread_mutex_unlock(&mutex);
            // Wakes up TA
            sem_post(&ta_sem);
        }
        else
        {
            cout << "No Seat Available, Student " << id <<" will come back later" << endl;
            sleep(3);
        }
    }
    return NULL;
}

int main()
{
    srand(time(NULL));
    int a;
    cout << "Enter Number of Students: ";
    cin >> a;
    int s[a];
    sem_init(&student_sem, 0, 3);
    sem_init(&ta_sem, 0, 0);
    pthread_t student_th[a];
    pthread_t ta_th;
    pthread_create(&ta_th, NULL, &TA, NULL);
    for (int i = 0; i < a; i++)
    {
        s[i] = i + 1;
        pthread_create(student_th + i, NULL, &Student, &s[i]);
    }

    pthread_join(ta_th, NULL);
    for (int i = 0; i < a; i++)
    {
        pthread_join(student_th[i], NULL);
    }
    sem_destroy(&student_sem);
    sem_destroy(&ta_sem);
    return 0;
}