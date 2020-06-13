#include "STAFF.h"

void Staff::ViewInfo()
{
	IUSER::ViewInfo();
	system("pause");
}

void Staff::showCourse()
{
	node<Course>* current = this->Courselist->head;
	while (current != 0)
	{
		current->data->viewInfo();
		current = current->next;
	}
}

void Staff::showStudent(string Class)
{
	bool valid = false;
	node<IUSER>* cur = userList->head;
	while (cur) {
		if (cur->data->getRole() == 1) {
			Student* ptrStudent = dynamic_cast<Student*>(cur->data);
			if (ptrStudent->getClassID() == Class) ptrStudent->ViewInfo();
			cout << endl;
			valid = true;
		}
		cur = cur->next;
	}
	if (valid == false) cout << "Invalid class !" << endl;
}

void Staff::showClass()
{
	node<CLASS>* current = this->ClassList->head;
	while (current != 0)
	{
		current->data->viewClassInfo();
		current = current->next;
	}
	system("pause");
}

void Staff::ImportClassFromFile()
{
	cout << "Please Place the file in Import folder and  press Enter to continue" << endl;
	cin.ignore();
	cin.get();
	cout << "Enter your class: ";
	string fileName;
	cin >> fileName;
	fstream* file = new fstream;
	file->open("import\\" + fileName + ".csv", ios::in);
	if (file->is_open())
	{
		linkedList<IUSER>* tmpUserList = new linkedList<IUSER>;
		string buffer;
		const string csvHeader = "No,Student ID,Fullname,gender,DoB,Class";
		getline(*file, buffer);
		if (buffer != csvHeader)
		{
			cout << "file is in wrong format" << endl;
			system("pause");
			delete file;
			return;
		}
		while (!file->eof())
		{
			getline(*file, buffer);
			cout << buffer << endl;
			buffer = StudentBufferCsv(buffer);
			node<IUSER>* userInstance = new node<IUSER>;
			userInstance->data = new Student;
			userInstance->data->init(buffer);
			node<IUSER>* tmp = this->userList->head;
			while (tmp != 0)
			{
				if (tmp->data->getID() == userInstance->data->getID())
				{
					cout << "Dupliate ID with existed Student\n";
					tmp->data->ViewInfo();
					cout << "\nStop importing from " + fileName + ".csv" << endl;
					cout << "Import failed - Roll back all changes\npress Enter to continue " << endl;
					cin.ignore();
					cin.get();
					delete tmpUserList;
					return;
				}
				tmp = tmp->next;
			}
			node<CLASS>* ClassTmp = this->ClassList->head;
			Student* stuPtr = dynamic_cast<Student*> (userInstance->data);
			while (ClassTmp != 0)
			{
				if (fileName == ClassTmp->data->getClassID())
				{
					if (stuPtr != 0)
					{
						linkedList<string>* CourseIDList = ClassTmp->data->getCourse();
						node<string>* CourseIDtmp = CourseIDList->head;
						while (CourseIDtmp != 0)
						{
							stuPtr->addCourse(*(CourseIDtmp->data));
							CourseIDtmp = CourseIDtmp->next;
						}
					}
				}
				ClassTmp = ClassTmp->next;
			}
			stuPtr->setCourseList(this->Courselist);
			tmpUserList->insertTop(userInstance);
		}
		this->userList->head = linkedList<IUSER>::joinList(tmpUserList, this->userList);
		cout << "Import finished \npress Enter to continue " << endl;
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "File Not found, press AnyKey to continue" << endl;
		cin.ignore();
		cin.get();
	}
	file->close();
	delete file;
}

void Staff::importCourseFromFile()
{
	cout << "Please Place the file in Import folder and  press Enter to continue" << endl;
	cin.ignore();
	cin.get();
	cout << "Enter your File (csv file): ";
	string fileName;
	cin >> fileName;
	fstream file;
	file.open("import\\" + fileName + ".csv", ios::in);
	bool isFirstLine = true;
	if (file.is_open())
	{
		linkedList<Course>* tempCourseList = new linkedList<Course>;
		string buffer;
		while (getline(file, buffer))
		{
			cout << buffer << endl;
			if (!isFirstLine)
			{
				buffer.erase(0, buffer.find(',') + 1); // delete the No, in input string
				node<Course>* courseInstance = new node<Course>;
				courseInstance->data = new Course(buffer);
				node<Course>* tmp = this->Courselist->head;
				while (tmp != 0)
				{
					if (tmp->data->ID == courseInstance->data->ID)
					{
						cout << "Dupliate ID with existed Course\n";
						tmp->data->viewInfo();
						cout << "\nStop importing from " + fileName + ".csv" << endl;
						cout << "Import failed - Roll back all changes\npress Enter to continue " << endl;
						cin.ignore();
						cin.get();
						delete tempCourseList;
						return;
					}
					tmp = tmp->next;
				}
				tempCourseList->insert(courseInstance);
			}
			else
			{
				const string csvHeader = "No,CourseID,Course name,Class ID,Lecturer ID,Start date,End date,Day of week,Start time,End time,Room";
				if (buffer != csvHeader)
				{
					cout << "file is in wrong format" << endl;
					system("pause");
					return;
				}
				isFirstLine = false;
			}
		}
		this->Courselist->head = linkedList<Course>::joinList(tempCourseList, this->Courselist);
		cout << "Import finished \npress Enter to continue " << endl;
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "File Not found, press AnyKey to continue" << endl;
		cin.ignore();
		cin.get();
	}
	file.close();
}

void Staff::editStudent()
{
	ConsoleUI studentMenu(10);
	if (userList->head)
	{
		userList->resetCurrent();
		do
		{
			if (userList->current->data->getRole() == STUDENT)
			{
				studentMenu.addLine(userList->current->data->getID() + " - " + userList->current->data->getName());
			}
		} while (userList->next());
		studentMenu.addLine("Back");
		bool isExit = false;
		while (!isExit)
		{
			while (!isExit)
			{
				studentMenu.clear();
				studentMenu.showMenu();
				studentMenu.getKey();
				if (studentMenu.getState())
				{
					if (studentMenu.getChoice() == studentMenu.exitChoice())
					{
						isExit = true;
					}
					else
					{
						userList->resetCurrent();
						int count = 0;
						do
						{
							if (count == studentMenu.getChoice())
							{
								break;
							}
							if (userList->current->data->getRole() == STUDENT)
							{
								++count;
							}
						} while (userList->next());
	  					//nếu người dùng là student tôi sẽ ép kiểu lại tại vì ko gọi hàm của student được từ class IUSER
	  					//tạo pointer là học sinh
	  					Student* ptrStudent = dynamic_cast<Student*>(userList->current->data);
	  					//gọi hàm thay đổi tên
	  					ConsoleUI EditMenu(10);
	  					EditMenu.addTitle("Edit option");
	  					EditMenu.addLine("Password");
	  					EditMenu.addLine("Change Class");
	  					EditMenu.addLine("Add Course");
	  					EditMenu.addLine("remove Course");
	  					EditMenu.addLine("Back");
	  					bool isBack = false;
						while (!isBack)
						{
							EditMenu.clear();
							EditMenu.showMenu();
							EditMenu.getKey();
							if (EditMenu.getState())
							{
								if (EditMenu.getChoice() == EditMenu.exitChoice())
								{
									isBack = true;
								}
								else
								{
									switch (EditMenu.getChoice())
									{
									case 0:
									{
										string pass, RePass;
										cout << "Enter new Password: ";
										cin >> pass;
										cout << "PLease re-enter new password: ";
										cin >> RePass;
										if (pass == RePass)
										{
											ptrStudent->setPassword(pass);
										}
										else
										{
											cout << "Password does not matched! ";
											system("PAUSE");
										}

										break;
									}
									case 1:
									{
										cout << "Enter New Class: ";
										string Class;
										cin >> Class;
										ptrStudent->ChangeClass(Class);
										break;
									}
									case 2:
									{
										cout << "Enter New Course: ";
										string course;
										cin >> course;
										ptrStudent->addCourse(course);
										break;
									}
									case 3:
									{
										cout << "Enter Course to Remove: ";
										string course;
										cin >> course;
										ptrStudent->addCourse(course);
										break;
									}
									default:
										break;
									}
								}
							}
						}
						system("Pause");
					}
				}
			}
		}
	}
}

Staff::Staff()
{
	this->role = STAFF;
}

void Staff::showAdvanceMenu(int choice)
{
	string StudentID, ClassID;
	//while (choice != 0)
	//{
	/*	system("CLS");
		cout << "1.Personal Info" << endl;
		cout << "2.Show all Course" << endl;
		cout << "3.Import Course from file" << endl;
		cout << "4.Show all class" << endl;
		cout << "5.Import Class from file" << endl;
		cout << "6.Show all Student" << endl;
		cout << "7.Change Student Info" << endl;
		cout << "8.Remove student" << endl;
		cout << "9.Change student class" << endl;
		cout << "10.Add student" << endl;
		cout << "11.Show student in a class" << endl;
		cout << "12.Add new coure" << endl;
		cout << "0.Log out" << endl;
		cout << "enter your choice:" << endl;
		cin >> choice;*/
	switch (choice)
	{
	case 0:
	{
		ImportClassFromFile();
		break;
	}
	case 1:
	{
		addStudent();
		break;
	}

	case 2:
	{
		editStudent();
		//chạy thử
		break;
	}
	case 3:
	{
		cout << "Input Student ID" << endl;
		cin.ignore();
		getline(cin, StudentID);
		removeStudent(StudentID);
		break;
	}
	case 4:
	{
		cout << "Input Student ID" << endl;
		cin.ignore();
		getline(cin, StudentID);
		cout << "Input Class ID" << endl;
		getline(cin, ClassID);
		change_student_class(ClassID, StudentID);
		break;
	}
	case 5:
	{
		showClass();
		break;
	}

	case 6:
	{
		cout << "enter ClassID: ";
		cin.ignore();
		getline(cin, ClassID);
		showStudent(ClassID);
		break;
	}
	case 7:
	{
		importCourseFromFile();
		break;
	}
	case 8:
	{
		addCourse();
		break;
	}
	case 9:
	{
		editCourse();
		break;
	}
	case 10:
	{
		removeCourse();
		break;
	}
	case 11:
		viewLecturer();
		system("pause");
		break;
	case 12:
		viewStudent();
		system("pause");
		break;	
	case 13:
	{
		showCourse();
		system("pause");
		break;
	}
	default:
		cout << "PLease Enter The choice you want" << endl;
		break;
	}
	//}
}



int Staff::init(string dataString)
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
	this->DoB = dataString;
	return 0;
}

void Staff::setCourseList(linkedList<Course>* Courselist)
{
	this->Courselist = Courselist;
}

void Staff::setClassList(linkedList<CLASS>* ClassList)
{
	this->ClassList = ClassList;
}

string Staff::parse()
{
	string parseResult = "0 " + this->ID + ',' + this->password + ',' + this->name + ',' + char(this->gender + 48) + ',' + this->DoB;
	return parseResult;
}

void Staff::setUserList(linkedList<IUSER>* UserList)
{
	this->userList = UserList;
}

void Staff::removeStudent(string studentID) {
	node<IUSER>* cur = userList->head;
	if (cur->data->getID() == studentID) {
		if (cur->data->getRole() == STUDENT) {
			userList->head = cur->next;
			delete cur;
			return;
		}
	}
	/*node<IUSER>* temp = cur;*/
	cur = cur->next;
	while (cur->next) {
		if (cur->next->data->getRole() == STUDENT) {
			if (cur->next->data->getID() == studentID)
			{
				node<IUSER>* tmp = cur;
				tmp->next = tmp->next->next;
				delete cur;
				return;
			}
		}
		cur = cur->next;
	}
}

void Staff::change_student_class(string ClassID, string StudentID) {
	node<IUSER>* cur = userList->head;
	while (cur != 0)
	{
		if (cur->data->getRole() == STUDENT)
		{
			if (cur->data->getID() == StudentID)
			{
				Student* ptrStudent = dynamic_cast<Student*>(cur->data);
				ptrStudent->ChangeClass(ClassID);
			}
		}
		cur = cur->next;
	}
}

void Staff::addStudent() {
	cout << "enter id: ";
	string id;
	getline(cin, id);
	if (checkDupID(id) == true) {
		cout << "the ID already exist!" << endl;
		system("pause");
		return;
	}
	else {
		cout << "enter name: "; string name;
		getline(cin, name);
		cout << "enter class: "; string which_class;
		getline(cin, which_class);
		int choice_gender = 5;
		while (choice_gender < 0 || choice_gender>1) {
			cout << "gender(0: male, 1: Female): ";
			cin >> choice_gender;
		}
		string gender;
		if (choice_gender == 0) gender = "0";
		else gender = "1";
		int tempY, tempM, tempD;
		bool check = false;
		bool leapYear = false;
		string day;
		string year;
		string month;
		cin.ignore();
		while (check == false) {
			cout << "Day of birth: " << endl;
			cout << "day: "; getline(cin, day);
			cout << "month: "; getline(cin, month);
			cout << "year: "; getline(cin, year);
			tempY = converter::strToInt(year);
			if ((tempY % 100) == 0) {
				if ((tempY % 400) == 0) leapYear = true;
			}
			else if ((tempY % 4) == 0) leapYear = true;
			tempM = converter::strToInt(month);
			if (tempM > 12 || tempM < 1) cout << "Invalid month input! (1 < month < 12)" << endl;
			else {
				tempD = converter::strToInt(day);
				if (tempM == 2) {
					if (leapYear == true) {
						if (tempD < 1 || tempD>29) cout << "Invalid day input! (1<day<29) (Feb) (leap year = true)" << endl;
						else check = true;
					}
					else {
						if (tempD < 1 || tempD>28) cout << "Invalid day input! (1<day<28) (Feb) (leap year = false)" << endl;
						else check = true;
					}
				}
				if (tempM == 1 || tempM == 3 || tempM == 5 || tempM == 7 || tempM == 8 || tempM == 10 || tempM == 12) {
					if (tempD < 1 || tempD>31) cout << "Invalid day input! (1<day<31) (" << monthConverter(tempM, 1) << ")" << endl;
					else check = true;
				}
				if (tempM == 4 || tempM == 6 || tempM == 9 || tempM == 11) {
					if (tempD < 1 || tempD>30) cout << "Invalid day input (1<day<30) (" << monthConverter(tempM, 1) << ")" << endl;
					else check = true;
				}
			}
		}
		if (tempD < 10) day = "0" + day;
		if (tempM < 10) month = "0" + month;
		string password = day + month + year;
		string dob = day + "-" + month + "-" + year;
		node<IUSER>* p = new node<IUSER>;
		p->data = new Student;
		p->data->init(id + "," + password + "," + name + "," + gender + "," + dob + "," + which_class);
		ClassList->resetCurrent();
		Student* ptrStudent = dynamic_cast<Student*>(p->data);
		if (ptrStudent)
		{
			ptrStudent->setCourseList(this->Courselist);
			if (ClassList->current)
			{
				do
				{
					if (ClassList->current->data->getClassID() == which_class)
					{
						ClassList->current->data->getCourse()->resetCurrent();
						if (ClassList->current->data->getCourse()->current)
						{
							do
							{
								ptrStudent->addCourse(*(ClassList->current->data->getCourse()->current->data));
							} while (ClassList->current->data->getCourse()->next());
						}
					}
				} while (ClassList->next());
			}
		}
		userList->insertTop(p);
		system("pause");
	}
}

string Staff::monthConverter(int month, int mode) {
	string res;
	if (mode == 1) {
		switch (month)
		{
		case 1: res = "Jan";
			break;
		case 2: res = "Feb";
			break;
		case 3: res = "Mar";
			break;
		case 4: res = "Apr";
			break;
		case 5: res = "May";
			break;
		case 6: res = "Jun";
			break;
		case 7: res = "Jul";
			break;
		case 8: res = "Aug";
			break;
		case 9: res = "Sep";
			break;
		case 10: res = "Oct";
			break;
		case 11: res = "Nov";
			break;
		case 12: res = "Dec";
			break;
		default:
			res = "Invalid month";
			break;
		}
	}
	if (mode == 2) {
		switch (month)
		{
		case 1: res = "January";
			break;
		case 2: res = "Febuary";
			break;
		case 3: res = "March";
			break;
		case 4: res = "April";
			break;
		case 5: res = "May";
			break;
		case 6: res = "June";
			break;
		case 7: res = "July";
			break;
		case 8: res = "August";
			break;
		case 9: res = "September";
			break;
		case 10: res = "October";
			break;
		case 11: res = "November";
			break;
		case 12: res = "December";
			break;
		default:
			res = "Invalid month";
			break;
		}
	}
	return res;
}

bool Staff::checkDupID(string ID) {
	node<IUSER>* cur = userList->head;
	while (cur) {
		if (cur->data->getID() == ID) return true;
		cur = cur->next;
	}
	return false;
}

void Staff::editCourse()
{
	ConsoleUI courselist(8);
	Courselist->resetCurrent();
	if (Courselist->current)
	{
		do
		{
			courselist.addLine(Courselist->current->data->ID + '-' + Courselist->current->data->courseName);
		} while (Courselist->next());
		courselist.addLine("Back");
		Courselist->resetCurrent();
		bool isExit = false;
		while (!isExit)
		{
			courselist.clear();
			courselist.showMenu();
			courselist.getKey();
			if (courselist.getState())
			{
				if (courselist.getChoice() == courselist.exitChoice())
				{
					isExit = true;
				}
				else
				{
					for (int i = 0; i < courselist.getChoice(); i++)
					{
						Courselist->next();
					}
					isExit = true;
				}
			}
		}
		ConsoleUI UI(11);
		UI.addTitle("What do you want to Edit");
		UI.addLine("Course Name");
		UI.addLine("Class");
		UI.addLine("Lecturer");
		UI.addLine("Start Date");
		UI.addLine("End Date");
		UI.addLine("Day Of Week");
		UI.addLine("Start Time");
		UI.addLine("End Time");
		UI.addLine("Room");
		UI.addLine("Back");
		isExit = false;
		while (!isExit)
		{
			UI.clear();
			UI.showMenu();
			UI.getKey();
			if (UI.getState())
			{
				if (UI.getChoice() == UI.exitChoice())
				{
					isExit = true;
				}
				else
				{
					switch (UI.getChoice())
					{
					case 0:
						cout << "Enter new name: ";
						getline(cin, Courselist->current->data->courseName);
						break;
					case 1:
						cout << "Enter new class: ";
						getline(cin, Courselist->current->data->ClassID);
						break;
					case 2:
						cout << "Enter new Lecturer ID: ";
						getline(cin, Courselist->current->data->lecturerID);
						break;
					case 3:
						cout << "Enter new Start Date: " << endl;
						do
						{
							cout << "Day: ";
							cin >> Courselist->current->data->startDate.day;
							cout << "Month: ";
							cin >> Courselist->current->data->startDate.month;
							cout << "Year: ";
							cin >> Courselist->current->data->startDate.year;
						} while (!checkDateInput(Courselist->current->data->startDate.day, Courselist->current->data->startDate.month, Courselist->current->data->startDate.year));
						break;
					case 4:
						cout << "Enter new End Date: " << endl;
						do
						{
							cout << "Day: ";
							cin >> Courselist->current->data->endDate.day;
							cout << "Month: ";
							cin >> Courselist->current->data->endDate.month;
							cout << "Year: ";
							cin >> Courselist->current->data->endDate.year;
						} while (!checkDateInput(Courselist->current->data->endDate.day, Courselist->current->data->endDate.month, Courselist->current->data->endDate.year));
						break;
					case 5:
						cout << "Enter Day of week (Mon = 0 -> Sun = 6): ";
						do
						{
							cin >> Courselist->current->data->dayOfweek;
						} while (Courselist->current->data->dayOfweek < 0 && Courselist->current->data->dayOfweek >6);
						break;
					case 6:
						cout << "Enter new Start Time: " << endl;
						do
						{
							cout << "Hour: ";
							cin >> Courselist->current->data->startTime.hour;
						} while (Courselist->current->data->startTime.hour > 23 && Courselist->current->data->startTime.hour < 0);
						do
						{
							cout << "Min: ";
							cin >> Courselist->current->data->startTime.minute;
						} while (Courselist->current->data->startTime.minute > 59 && Courselist->current->data->startTime.minute < 0);
						break;
					case 7:
						cout << "Enter new End Time: " << endl;
						do
						{
							cout << "Hour: ";
							cin >> Courselist->current->data->endTime.hour;
						} while (Courselist->current->data->endTime.hour > 23 && Courselist->current->data->endTime.hour < 0);
						do
						{
							cout << "Min: ";
							cin >> Courselist->current->data->endTime.minute;
						} while (Courselist->current->data->endTime.minute > 59 && Courselist->current->data->endTime.minute < 0);
						break;
					case 8:
						cout << "Enter new Room ID: ";
						cin >> Courselist->current->data->room;
						break;
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void Staff::addCourse()
{
	cout << "Course ID:";
	string courseID;
	getline(cin, courseID);
	if (checkDupID(courseID) == true) {
		cout << "the ID already exist!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "Course Name:";
		string courseName;
		getline(cin, courseName);
		cout << "Lecturer Name:";
		string lecturerName;
		getline(cin, lecturerName);
		cout << "Class Name:";
		string className;
		getline(cin, className);
		cout << "Start Date:";
		string startDate;
		getline(cin, startDate);
		cout << "End Date:";
		string endDate;
		getline(cin, endDate);
		string dow;
		getline(cin, dow);
		cout << "Start Hour:";
		string startHour;
		getline(cin, startHour);
		cout << "End hour:";
		string endHour;
		getline(cin, endHour);
		cout << "Room:";
		string room;
		getline(cin, room);
		node<Course>* p = new node<Course>;
		p->data = new Course(courseID + "," + courseName + "," + lecturerName + "," + className + "," + startDate + "," + endDate + ',' + dow + "," + startHour + "," + endHour + "," + room);
		Courselist->insert(p);
	}


}
void Staff::viewStudent()
{
	ConsoleUI CourseMenu(10);
	if (Courselist->head)
	{
		Courselist->resetCurrent();
		do
		{
			CourseMenu.addLine(Courselist->current->data->ID + " - " + Courselist->current->data->courseName);
		} while (Courselist->next());
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
					Courselist->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice(); i++)
					{
						Courselist->next();
					}
					userList->resetCurrent();
					if (userList->current);
					{
						do {
							Student* Stu = dynamic_cast<Student*>(userList->current->data);
							if (Stu)
							{
								if (Stu->isEnrolled(Courselist->current->data->ID))
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
void Staff::viewLecturer()
{
	ConsoleUI CourseMenu(10);
	if (Courselist->head)
	{
		Courselist->resetCurrent();
		do
		{
			CourseMenu.addLine(Courselist->current->data->ID + " - " + Courselist->current->data->courseName);
		} while (Courselist->next());
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
					Courselist->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice(); i++)
					{
						Courselist->next();
					}
					userList->resetCurrent();
					do
					{
						if (userList->current->data->getRole() == LECTURER && userList->current->data->getID() == Courselist->current->data->lecturerID)
						{
							userList->current->data->ViewInfo();
							break;
						}
					}while(userList->next());
				}
			}
		}
	}
	
}
void Staff::removeCourse()
{
	ConsoleUI CourseMenu(10);
	CourseMenu.addTitle("Choose Course to remove");
	if (Courselist->head)
	{
		Courselist->resetCurrent();
		do
		{
			CourseMenu.addLine(Courselist->current->data->ID + " - " + Courselist->current->data->courseName);
		} while (Courselist->next());
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
					Courselist->resetCurrent();
					for (int i = 0; i < CourseMenu.getChoice()-1; i++)
					{
						Courselist->next();
					}
					if (Courselist->current == Courselist->head)
					{
						Courselist->head = Courselist->head->next;
						delete Courselist->current;
					}
					else
					{
						node<Course>* tmp = Courselist->current->next;
						Courselist->current->next = Courselist->current->next->next;
						delete tmp;
					}
					Courselist->resetCurrent();
					isExit = true;
				}
			}
		}
	}
}
bool Staff::checkDateInput(int day, int month, int year) {
	bool leapYear = false, check = false;
	if ((year % 100) == 0) {
		if ((year % 400) == 0) leapYear = true;
	}
	else if ((year % 4) == 0) leapYear = true;
	if (month > 12 || month < 1) {
		cout << "Invalid month input! (1 < month < 12)" << endl;
		return false;
	}
	else {
		if (month == 2) {
			if (leapYear == true) {
				if (day < 1 || day>29) {
					cout << "Invalid day input! (1<day<29) (Feb) (leap year = true)" << endl;
					return false;
				}
			}
			else {
				if (day < 1 || day>28) {
					cout << "Invalid day input! (1<day<28) (Feb) (leap year = false)" << endl;
					return false;
				}
			}
		}
		if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			if (day < 1 || day>31) {
				cout << "Invalid day input! (1<day<31) (" << monthConverter(month, 1) << ")" << endl;
				return false;
			}
		}
		if (month == 4 || month == 6 || month == 9 || month == 11) {
			if (day < 1 || day>30) {
				cout << "Invalid day input (1<day<30) (" << monthConverter(month, 1) << ")" << endl;
				return false;
			}
		}
	}
	return true;
}
string Staff::getDate(int day, int month, int year, int type) {
	if (type == 1) {
		if (month < 10 && day>10) return to_string(day) + "/0" + to_string(month) + "/" + to_string(year);
		if (month > 10 && day < 10) return "0" + to_string(day) + "/" + to_string(month) + "/" + to_string(year);
		if (month < 10 && day < 10) return "0" + to_string(day) + "/0" + to_string(month) + "/" + to_string(year);
		return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
	}
	if (type == 2) {
		if (month < 10 && day>10) return to_string(day) + "-0" + to_string(month) + "-" + to_string(year);
		if (month > 10 && day < 10) return "0" + to_string(day) + "-" + to_string(month) + "-" + to_string(year);
		if (month < 10 && day < 10) return "0" + to_string(day) + "-0" + to_string(month) + "-" + to_string(year);
		return to_string(day) + "-" + to_string(month) + "-" + to_string(year);
	}
	if (type == 3) {
		if (day == 1) return monthConverter(month, 1) + " " + to_string(day) + "st " + to_string(year);
		if (day == 2) return monthConverter(month, 1) + " " + to_string(day) + "nd " + to_string(year);
		if (day == 3) return monthConverter(month, 1) + " " + to_string(day) + "rd " + to_string(year);
		return monthConverter(month, 1) + " " + to_string(day) + "th " + to_string(year);
	}
	if (type == 4) {
		if (day == 1) return  to_string(day) + "st " + monthConverter(month, 1) + " " + to_string(year);
		if (day == 2) return  to_string(day) + "nd " + monthConverter(month, 1) + " " + to_string(year);
		if (day == 3) return  to_string(day) + "rd " + monthConverter(month, 1) + " " + to_string(year);
		return  to_string(day) + "th " + monthConverter(month, 1) + " " + to_string(year);
	}
	if (type == 5) {
		if (day == 1) return monthConverter(month, 2) + " " + to_string(day) + "st " + to_string(year);
		if (day == 2) return monthConverter(month, 2) + " " + to_string(day) + "nd " + to_string(year);
		if (day == 3) return monthConverter(month, 2) + " " + to_string(day) + "rd " + to_string(year);
		return monthConverter(month, 2) + " " + to_string(day) + "th " + to_string(year);
	}
	if (type == 6) {
		if (day == 1) return  to_string(day) + "st " + monthConverter(month, 2) + " " + to_string(year);
		if (day == 2) return  to_string(day) + "nd " + monthConverter(month, 2) + " " + to_string(year);
		if (day == 3) return  to_string(day) + "rd " + monthConverter(month, 2) + " " + to_string(year);
		return  to_string(day) + "th " + monthConverter(month, 2) + " " + to_string(year);
	}
	else return "invalid date";
}

string StudentBufferCsv(string buffer)
{
	size_t commaPos = buffer.find(',');
	buffer.erase(0, commaPos + 1);
	commaPos = buffer.find(',');
	size_t nextCommaPos = buffer.find(',', commaPos + 1);
	nextCommaPos = buffer.find(',', nextCommaPos + 1);
	string dob = buffer.substr(nextCommaPos + 1, buffer.find(',', nextCommaPos + 1) - nextCommaPos - 1);
	while (dob.find('-') != string::npos)
	{
		dob.erase(dob.find('-'), 1);
	}
	buffer.insert(commaPos, ',' + dob);
	return buffer;
}
