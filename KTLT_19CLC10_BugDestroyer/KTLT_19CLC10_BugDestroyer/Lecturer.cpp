#include "Lecturer.h"

Lecturer::Lecturer()
{
	this->role = LECTURER;
}

int Lecturer::init(string dataString)
{
	int commaPos = dataString.find(',');
	this->ID = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);


	commaPos = dataString.find(',');
	this->password = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	commaPos = dataString.find(',');
	this->name = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	commaPos = dataString.find(',');
	this->gender = strToInt(dataString.substr(0, commaPos));
	dataString.erase(0, commaPos + 1);

	commaPos = dataString.find(',');
	this->DoB = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	this->degree = dataString;

	return 0;
}

void Lecturer::setUserList(linkedList<IUSER>* userList)
{
	this->userList = userList;
}

void Lecturer::setCourseList(linkedList<Course>* Courselist)
{
	this->CourseList = Courselist;
}

void Lecturer::showMenu()
{
}

string Lecturer::parse()
{
	string parseResult = "2 " + this->ID + ',' + this->password + ',' + this->name + ',' + char(this->gender + 48) + ',' + this->DoB + ',' + this->degree;
	return parseResult;
}

void Lecturer::ViewInfo()
{
}
