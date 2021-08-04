#include <iostream>
#include <pthread.h>
using namespace std;

struct Student {
    string name;
    int age;
    double absolute;
    string grade;
};

void * calcGrade(void *temp){
    Student arg = *(Student *)temp;
    double absolutes = arg.absolute;
    if (absolutes >= 90)
        arg.grade = "A+";
    else if (absolutes >= 86 && absolutes <= 89)
        arg.grade = "A";
    else if (absolutes >= 82 && absolutes <= 85)
        arg.grade = "A-";
    else if (absolutes >= 78 && absolutes <= 81)
        arg.grade = "B+";
    else if (absolutes >= 74 && absolutes <= 77)
        arg.grade = "B";
    else if (absolutes >= 70 && absolutes <= 73)
        arg.grade = "B-";
    else if (absolutes >= 66 && absolutes <= 69)
        arg.grade = "C+";
    else if (absolutes >= 62 && absolutes <= 65)
        arg.grade = "C";
    else if (absolutes >= 58 && absolutes <= 61)
        arg.grade = "C-";
    else if (absolutes >= 54 && absolutes <= 57)
        arg.grade = "D+";
    else if (absolutes >= 50 && absolutes <= 53)
        arg.grade = "D";
    else if (absolutes <= 49)
        arg.grade = "F";
    *(Student *)temp = arg;
    return temp;
}

int main(){
    Student obj;
    cout << "Enter your Name: ";
    cin >> obj.name;
    cout << "Enter your Age: ";
    cin >> obj.age;
    cout << "Enter your Absolutes: ";
    cin >> obj.absolute;
    pthread_t th;
    Student *temp;
    pthread_create(&th, NULL, &calcGrade, &obj);
    pthread_join(th, (void**)&temp);
    cout << temp->name << endl;
    cout << temp->age << endl;
    cout << temp->absolute << endl;
    cout << temp->grade << endl;
}