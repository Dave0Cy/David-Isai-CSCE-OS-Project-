#include <iostream>
#include <fstream>
#include <pthread.h>
#include <stdio.h>
#include <iomanip>


using namespace std;

const int total = 100;//To make the array fixed
double Passed;
int size = 0;

struct input {
	int StudentID;//the first numbers
	int Final;//1 or 0 if they passed or failed
};


void* StudentsPassed(void* pass) {
	input* students = (input*)pass;
	double count = 0;

	for(int i = 0; i < total; i++) {
		if(students[i].Final == 1 ) {
			count ++;
		}
	}
	Passed = (count /size) * 100;
	pthread_exit(0);
}

int main() {
	ifstream inputfile("students.txt");
	input Students[total];
	int ID;
	int FinalGrade;
	int RealTotal = 0; // The actual number of students in the input file

	while (RealTotal < total) {//Keeps looping so that all of the array can be inputed and stored
		if (inputfile >> ID >> FinalGrade) {//reads inputfile then takes out the id and finalgrade
			Students[RealTotal] = { ID,FinalGrade };//stores what was taken from the inputfile
			RealTotal++;
		}
		else {
			break;//When its done reading
		}
	}
    size = RealTotal;
	//From notes
	pthread_t tid;// Thread Identifier
	pthread_create(&tid,NULL,StudentsPassed,Students);//Creates threaded that will calculate
	pthread_join(tid,NULL);//waits for the thread to finish

	cout <<setprecision(4) << "The percentage of students that passed was: " << Passed << "%\n";

	return 0;
}