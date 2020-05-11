#include <iostream>
#include<fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct Student
{
	int No1;
	string coureID, className, courseName, users, lecturerName, degree, gender, startDate;
	string endDate;
	string dayofWeek, startHour, startMinute, endHour, endMinute, room;


};

void load(ifstream& f1, Student& s, vector<Student>& list_student);
void save(ofstream& f2, vector<Student>list_student);