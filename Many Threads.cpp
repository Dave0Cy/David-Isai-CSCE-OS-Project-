#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <iomanip>

using namespace std;

const int total = 100;  // Too make the array fixed
double Passed;
int size = 0;

struct input {
    int StudentID;  // the first numbers
    int Final;      // 1 or 0 if they passed or failed
};

// Acts as main thread ( like an a fork-join parralleism)that calculated the amount of students that passed
int globalPassCount = 0;

// Thread Process that checks if student passed or failed
void* ProcessStudent(void* arg) {
    input* student = (input*)arg;

    if (student->Final == 1) {
        globalPassCount++;  
    }

    pthread_exit(0);
}

int main() {
    ifstream inputfile("students.txt");
    input Students[total];
    int ID;
    int FinalGrade;
    int RealTotal = 0;  // The actual number of students in the input file

    while (RealTotal < total) {//Keeps looping so that all of the array can be inputed and stored
        if (inputfile >> ID >> FinalGrade) {//reads inputfile then takes out the id and finalgrade
            Students[RealTotal] = {ID, FinalGrade};//stores what was taken from the inputfile
            RealTotal++;
        } else {
            break;//When its done reading
        }
    }
    size = RealTotal;

    // Creates one thread per student
    pthread_t threads[total];

    for (int i = 0; i < size; ++i) {
        pthread_create(&threads[i], NULL, ProcessStudent, (void*)&Students[i]);
    }

    // Wait for threads to complete
    for (int i = 0; i < size; ++i) {
        pthread_join(threads[i], NULL);
    }

    Passed = (double)globalPassCount / size * 100;

    cout << setprecision(4) << "The percentage of students that passed was: " << Passed << "%\n";

    return 0;
}
