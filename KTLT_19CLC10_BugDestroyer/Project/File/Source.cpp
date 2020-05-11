#include "Header.h"

void load(ifstream& f1, Student& s, vector<Student>& list_student)
{
	

	string No1 = "";
	string coureID = "";
	string courseName = "";
	string className = "";
	string users = "";
	string lecturerName = "";
	string degree = "";
	string gender = "";
	string startDate = "";
	string endDate = "";
	string dayofWeek = "";
	string startHour = "";
	string startMinute = "";
	string endHour = "";
	string endMinute = "";
	string room = "";


	while (!f1.eof())
	{
		getline(f1, No1, ',');
		getline(f1, coureID, ',');
		getline(f1, courseName, ',');
		getline(f1, className, ',');
		getline(f1, users, ',');
		getline(f1, lecturerName, ',');
		getline(f1, degree, ',');
		getline(f1, gender, ',');
		getline(f1, startDate, ',');
		getline(f1, endDate, ',');
		getline(f1, dayofWeek, ',');
		getline(f1, startHour, ',');
		getline(f1, startMinute, ',');
		getline(f1, endHour, ',');
		getline(f1, endMinute, ',');
		getline(f1, room, '\n');
		if (f1.fail())
		{
			break;
		}
		s.No1 = stof(No1);
		s.coureID = coureID;
		s.className = className;
		s.courseName = courseName;
		s.users = users;
		s.lecturerName = lecturerName;
		s.degree = degree;
		s.gender = gender;
		s.startDate = startDate;
		s.endDate = endDate;
		s.dayofWeek = dayofWeek;
		s.startHour = startHour;
		s.startMinute = startMinute;
		s.endHour = endHour;
		s.endMinute = endMinute;
		s.room = room;
		list_student.push_back(s);
	}
}

void save(ofstream& f2, vector<Student>list_student) {
	for (int i = 0; i < list_student.size(); i++)
	{
		f2 << "No: " << list_student[i].No1 << endl;
		f2 << "ID: " << list_student[i].coureID << endl;
		f2 << "Class: " << list_student[i].className << endl;
		f2 << "Name student: " << list_student[i].courseName << endl;
		f2 << "Lecturer user: " << list_student[i].users << endl;
		f2 << "Lecturere name: " << list_student[i].lecturerName << endl;
		f2 << "Lecturer degree: " << list_student[i].degree << endl;
		f2 << "Literature gender: " << list_student[i].gender << endl;
		f2 << "Start date: " << list_student[i].startDate << endl;
		f2 << "End date: " << list_student[i].endDate << endl;
		f2 << "Day of week: " << list_student[i].dayofWeek << endl;
		f2 << "Start hour: " << list_student[i].startHour << endl;
		f2 << "Start minute: " << list_student[i].startMinute << endl;
		f2 << "End hour: " << list_student[i].endHour << endl;
		f2 << "End minute: " << list_student[i].endMinute << endl;
		f2 << "Room: " << list_student[i].room << endl;

		f2 << '\n';
	}
}