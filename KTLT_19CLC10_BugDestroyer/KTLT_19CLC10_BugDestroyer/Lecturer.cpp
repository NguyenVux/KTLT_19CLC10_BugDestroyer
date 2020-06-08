#include "Lecturer.h"

void Lecturer::showAllCourse()
{
	node<Course>* currentCourse = CourseList->head;
	while (currentCourse)
	{
		currentCourse->data->viewInfo();
		currentCourse = currentCourse->next;
	}
}

void Lecturer::showMyCourse()
{
	node<Course>* currentCourse = CourseList->head;
	while (currentCourse)
	{
		if (currentCourse->data->lecturerID == this->ID)
		{
			currentCourse->data->viewInfo();
			
		}
		currentCourse = currentCourse->next;
	}
}

void Lecturer::viewCourseAttendances()
{
	cout << "Enter CourseID to view Attendances: ";
	string courseID;
	cin >> courseID;
	node<IUSER>* userNode = userList->head;
	while (userNode)
	{
		if (userNode->data->getRole() == STUDENT)
		{
			Student* studentPtr = dynamic_cast<Student*>(userNode->data);
			if (studentPtr)
			{
				if (studentPtr->isEnrolled(courseID))
				{
					studentPtr->ViewInfo();
				}
			}
		}
		userNode = userNode->next;
	}
}

void Lecturer::EditCourseAttendances()
{
	cout << "Enter CourseID to Edit: ";
	string courseID;
	cin >> courseID;
	cout << "Enter Student ID: ";
	string studentID;
	cin >> studentID;
	node<IUSER>* currStudent = userList->head;;
	while (currStudent)
	{
		if (currStudent->data->getRole() == STUDENT && currStudent->data->getID() == studentID)
		{
			Student* ptr = dynamic_cast<Student*>(currStudent->data);
			if (ptr)
			{
				if (ptr->isEnrolled(courseID))
				{
					ptr->removeCourse(courseID);
					break;
				}
			}
		}
		currStudent = currStudent->next;
	}
}

void Lecturer::viewScoreBoard()
{
	cout << "Enter CourseID to view ScoreBoard: ";
	string courseID;
	cin >> courseID;
	SCOREBOARD scoreboard(courseID);
	int cellSize = 30;
	int scoreCellSize = 10;
	cout << endl << "|" << left << setw(cellSize) << ioHelper::centered("Student Name", cellSize) << "|"
		<< left << setw(scoreCellSize) << ioHelper::centered("MidTerm", scoreCellSize) << "|"
		<< left << setw(scoreCellSize) << ioHelper::centered("Final", scoreCellSize) << "|"
		<< left << setw(scoreCellSize) << ioHelper::centered("Lab", scoreCellSize) << "|"
		<< left << setw(scoreCellSize) << ioHelper::centered("Bonus", scoreCellSize) << "|";
	do
	{
		ScoreRecord rec = scoreboard.getCurrent();
		node<IUSER>* currUser = userList->head;
		while (currUser)
		{
			if (currUser->data->getID() == rec.studentID)
			{
				break;
			}
			currUser = currUser->next;
		}
		if (currUser)
		{
			cout << endl << "|" << left << setw(cellSize) << currUser->data->getName() << "|"
				<< left << setw(scoreCellSize);
			rec.midTerm > 5 ? ioHelper::textGreen() : rec.midTerm == 5 ? ioHelper::textYellow() : ioHelper::textRed();
			cout << ioHelper::centered(to_string(rec.midTerm).substr(0, 3), scoreCellSize);
			ioHelper::blackLine();
			cout << "|" << left << setw(scoreCellSize);

			rec.final > 5 ? ioHelper::textGreen() : rec.final == 5 ? ioHelper::textYellow() : ioHelper::textRed();
			cout << ioHelper::centered(to_string(rec.final).substr(0, 3), scoreCellSize);
			ioHelper::blackLine();
			cout << "|" << left << setw(scoreCellSize);


			rec.lab > 5 ? ioHelper::textGreen() : rec.lab == 5 ? ioHelper::textYellow() : ioHelper::textRed();
			cout << ioHelper::centered(to_string(rec.lab).substr(0, 3), scoreCellSize);
			ioHelper::blackLine();
			cout << "|" << left << setw(scoreCellSize);

			cout << left << setw(scoreCellSize) << ioHelper::centered(to_string(rec.bonus).substr(0, 3), scoreCellSize) << "|";
		}
	} while (scoreboard.next());	
}

void Lecturer::importScoreBoard()
{
	cout << "Place the csv file in import folder" << endl;
	system("pause");
	string courseID;
	cout << "Enter CSV file name: ";
	cin >> courseID;
	SCOREBOARD scoreboard(courseID,IMPORT);
}

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

void Lecturer::showAdvanceMenu(int choice)
{
	
	system("cls");
	switch (choice)
	{
	case 0:
		showAllCourse();
		cin.ignore();
		cin.get();
		break;
	case 1:
		showMyCourse();
		cin.ignore();
		cin.get();
		break;
	case 2:
		viewCourseAttendances();
		cin.ignore();
		cin.get();
		break;
	case 3:
		EditCourseAttendances();
		cin.ignore();
		cin.get();
		break;
	case 4:
		viewScoreBoard();
		cin.ignore();
		cin.get();
		break;
	case 5:
		importScoreBoard();
		cin.ignore();
		cin.get();
		break;
	}
}

string Lecturer::parse()
{
	string parseResult = "2 " + this->ID + ',' + this->password + ',' + this->name + ',' + char(this->gender + 48) + ',' + this->DoB + ',' + this->degree;
	return parseResult;
}

void Lecturer::ViewInfo()
{
	IUSER::ViewInfo();
	if (this->degree == "TS")
	{
		cout << "Degree: " << "Tien Si" << endl;
	}
	else if (this->degree == "tS")
	{
		cout << "Degree: " << "Thac Si" << endl;
	}
	else if (this->degree == "CN")
	{
		cout << "Degree: " << "Cu Nhan" << endl;
	}
	else
	{
		cout << "Degree: " << "unknown" << endl;
	}
	
	system("pause");
}
