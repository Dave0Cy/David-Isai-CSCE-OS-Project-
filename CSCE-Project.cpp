#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

const int total = 100;//To make the array fixed

struct input {
    int StudentID;//the first numbers 
    int Final;//1 or 0 if they passed or failed
};

double StudentsPassed( input students[], int Total) {
    int count = 0;
    for (int i = 0; i < Total;i++) {
        if (students[i].Final == 1) {
            count++;
        }
    }
    return (count * 100.0) / Total;
}

int main() {
    ifstream inputfile("students.txt");
    input Students[total];
    int ID;
    int FinalGrade;
    int RealTotal = 0;//The actual number of students in the input file 
    double passed;

    while (inputfile >> ID >> FinalGrade && RealTotal < total) {
        Students[RealTotal] = { ID,FinalGrade };
        RealTotal++;
    }

    passed = StudentsPassed(Students, RealTotal);
    cout << setprecision(4) << "The percentage of students that passed was: " << passed << "%" << endl;

    return 0;
}