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
	ConsoleUI CourseMenu(10);
	if (CourseList->head)
	{
		CourseList->resetCurrent();
		do
		{
			CourseMenu.addLine(CourseList->current->data->ID + " - " + CourseList->current->data->courseName);
		} while (CourseList->next());
		CourseMenu.addLine("Back");
		bool isExit = false;
		while (!isExit)
		{
			CourseMenu.clear();
			CourseMenu.showMenu();
			CourseMenu.getKey();
			if (CourseMenu.getState())
			{
				if (CourseMenu.exitChoice() == CourseMenu.getChoice())
				{
					isExit = true;
				}
				else
				{
					CourseList->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice(); i++)
					{
						CourseList->next();
					}
					userList->resetCurrent();
					if (userList->current);
					{
						do {
							Student* Stu = dynamic_cast<Student*>(userList->current->data);
							if (Stu)
							{
								if (Stu->isEnrolled(CourseList->current->data->ID))
								{
									Stu->ViewInfo();
									cout << "-------------------------------------------\n";
								}
							}
						} while (userList->next());
						system("PAUSE");
					}
				}
			}
		}
	}
}

void Lecturer::EditScoreBoard()
{
	ConsoleUI CourseMenu(10);
	if (CourseList->head)
	{
		CourseList->resetCurrent();
		do
		{
			if (CourseList->current->data->lecturerID == this->ID)
			{
				CourseMenu.addLine(CourseList->current->data->ID + " - " + CourseList->current->data->courseName);
			}
		} while (CourseList->next());
		CourseMenu.addLine("Back");
		bool isExit = false;
		while (!isExit)
		{
			CourseMenu.clear();
			CourseMenu.showMenu();
			CourseMenu.getKey();
			if (CourseMenu.getState())
			{
				if (CourseMenu.exitChoice() == CourseMenu.getChoice())
				{
					isExit = true;
				}
				else
				{
					CourseList->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice(); i++)
					{
						CourseList->next();
					}
					SCOREBOARD ScoreBoard(CourseList->current->data->ID);
					ScoreBoard.Edit();
					system("PAUSE");
				}
			}
		}
	}
}


void Lecturer::viewScoreBoard()
{
	ConsoleUI CourseMenu(10);
	if (CourseList->head)
	{
		CourseList->resetCurrent();
		do
		{
			if (CourseList->current->data->lecturerID == this->ID)
			{
				CourseMenu.addLine(CourseList->current->data->ID + " - " + CourseList->current->data->courseName);
			}
		} while (CourseList->next());
		CourseMenu.addLine("Back");
		bool isExit = false;
		while (!isExit)
		{
			CourseMenu.clear();
			CourseMenu.showMenu();
			CourseMenu.getKey();
			if (CourseMenu.getState())
			{
				if (CourseMenu.exitChoice() == CourseMenu.getChoice())
				{
					isExit = true;
				}
				else
				{
					CourseList->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice(); i++)
					{
						CourseList->next();
					}
					//===========================================
					SCOREBOARD scoreboard(CourseList->current->data->ID);					
					if (scoreboard.getResult())
					{
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
					system("PAUSE");
					//===========================================
				}
			}
		}
	}	
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
		viewScoreBoard();
		cin.ignore();
		cin.get();
		break;
	case 4:
		importScoreBoard();
		cin.ignore();
		cin.get();
		break;
	case 5:
		EditScoreBoard();
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
