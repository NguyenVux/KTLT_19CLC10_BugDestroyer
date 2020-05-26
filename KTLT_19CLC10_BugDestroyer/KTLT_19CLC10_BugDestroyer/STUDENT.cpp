#include "Student.h"

void Student::ViewInfo()
{
	cout << "ID: " << this->ID << endl;
	cout << "Name: " << this->name << endl;
	if (gender == MALE)
	{
		cout << "Gender: Male" << endl;
	}
	else
	{
		cout << "Gender: Female" << endl;
	}
	cout << "Day of Birth: " << this->DoB << endl;
	cout << "class: " << this->ClassID << endl;
}

void Student::showEnrolledCourse()
{
	CourseID.current = CourseID.head;
	while (CourseID.current != 0)
	{
		node<Course>* tmp = CourseList->head;
		while (tmp != 0)
		{
			if (tmp->data->ID == *(CourseID.current->data))
			{
				tmp->data->viewInfo();
			}
			tmp = tmp->next;
		}
		CourseID.current = CourseID.current->next;
	}
}

void Student::showAllCourse()
{
	node<Course>* tmp = CourseList->head;
	while (tmp != 0)
	{
		tmp->data->viewInfo();
		tmp = tmp->next;
	}
}

Student::Student()
{
	this->role = STUDENT;
}

void Student::showMenu()
{
	int choice = 0;
	while (choice != -1)
	{
		cout << "View My Course" << endl;
		cout << "View All Course" << endl;
		cout << "View All info" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			showEnrolledCourse();
			cin.ignore();
			cin.get();
			break;
		case 2:
			showAllCourse();
			cin.ignore();
			cin.get();
			break;
		case 3:
			ViewInfo();
			cin.ignore();
			cin.get();
			break;
		}
	}
	//ViewInfo();
}

int Student::init(string dataString)
{
	int commaPos = dataString.find(',');
	if (dataString.find(' ') == string::npos)
	{
		return 1;
	}
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
	
	commaPos = dataString.find(',');
	this->ClassID = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	if (dataString.find(',') != string::npos)
	{
		while (dataString.find(',') != string::npos)
		{
			node<string>* CourseIdNode = new node <string>;
			CourseIdNode->data = new string;
			commaPos = dataString.find(',');
			*(CourseIdNode->data) = dataString.substr(0, commaPos);
			dataString.erase(0, commaPos + 1);
			this->CourseID.insertTop(CourseIdNode);
		}
		node<string>* CourseIdNode = new node <string>;
		CourseIdNode->data = new string;
		*(CourseIdNode->data) = dataString;
		this->CourseID.insertTop(CourseIdNode);
	}
	
}

void Student::addCourse(string CourseID)
{
	node<string>* courseIdCurrent = this->CourseID.head;
	while (courseIdCurrent != 0)
	{
		if (CourseID == *(courseIdCurrent->data))
		{
			return;
		}
		courseIdCurrent = courseIdCurrent->next;
	}
	node<string>* CourseIdNode = new node <string>;
	CourseIdNode->data = new string;
	*(CourseIdNode->data) = CourseID;
	this->CourseID.insertTop(CourseIdNode);
}
void Student::setCourseList(linkedList<Course>* courseList)
{
	this->CourseList = courseList;
}

//Thay đổi tên
void Student::setName(string newName)
{
	name = newName;
}

void Student::setDoB(string newDoB)
{
	DoB = newDoB;
}






string Student::parse()
{
	string parseResult = "1 " + this->ID + ',' + this->password + ',' + this->name + ',' + char(this->gender + 48) + ',' + this->DoB+','+this->ClassID;
	node<string>* courseIdCurrent = this->CourseID.head;
	while (courseIdCurrent != 0)
	{
		parseResult += ',' + *(courseIdCurrent->data);
		courseIdCurrent = courseIdCurrent->next;
	}
	return parseResult;
}

void Student::ChangeClass(string ClassID) {
	this->ClassID = ClassID;
}

string Student::getClassID() {
	return this->ClassID;
}