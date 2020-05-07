#include "STAFF.h"

void Staff::ViewInfo()
{
	cout << "ID: " << this->ID << endl;
	cout << "Name: " << this->name << endl;
	if (gender == MALE)
	{
		cout << "Gender: Male"<< endl;
	}
	else
	{
		cout << "Gender: Female" << endl;
	}
	cout << "Day of Birth: " << this->DoB << endl;

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

void Staff::showStudent()
{
}

void Staff::showClass()
{
	node<CLASS>* current = this->ClassList->head;
	while (current != 0)
	{
		current->data->viewClassInfo();
		current = current->next;
	}
}

void Staff::ImportClassFromFile()
{
	cout << "Please Place the file in Import folder and  press Enter to continue" << endl;
	cin.ignore();
	cin.get();
	cout << "Enter your class: " ;
	string fileName;
	cin >> fileName;
	fstream* file = new fstream;
	file->open("import\\"+fileName+".csv", ios::in);
	if (file->is_open())
	{
		linkedList<IUSER>* tmpUserList = new linkedList<IUSER>;
		while (!file->eof())
		{
			string buffer;
			getline(*file, buffer);
			cout << buffer << endl;
			node<IUSER>* userInstance = new node<IUSER>;
			userInstance->data = new Student;
			userInstance->data->init(buffer + "," + fileName);
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
	fstream* file = new fstream;
	file->open("import\\" + fileName + ".csv", ios::in);
	
	if (file->is_open())
	{
		linkedList<Course>* tempCourseList = new linkedList<Course>;
		while (!file->eof())
		{	
			
			string buffer;
			getline(*file, buffer);
			cout << buffer << endl;
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
			tempCourseList->insertTop(courseInstance);			
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
	file->close();
	delete file;
}

Staff::Staff()
{
	this->role = STAFF;
}

void Staff::showMenu()
{
	int choice = -1;
	while (choice != 0)
	{
		system("CLS");
		cout << "1.Personal Info" << endl;
		cout << "2.Show all Course" << endl;
		cout << "3.Import Course from file" << endl;
		cout << "4.Show all class" << endl;
		cout << "5.Import Class from file" << endl;
		cout << "6.Show all Student" << endl;
		cout << "0.Log out" << endl;
		cout << "enter your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			ViewInfo();
			break;
		case 2:
			showCourse();
			system("pause");
			break;
		case 3:
			importCourseFromFile();
			break;
		case 4:
			showClass();
			break;
		case 5:
			ImportClassFromFile();
			break;
		default:
			cout << "PLease Enter The choice you want" << endl;
			break;
		}
	}
}


int Staff::init(string dataString)
{
	int commaPos = dataString.find(',');
	if (dataString.find(' ') == string::npos)
	{
		return 1;
	}
	this->ID = dataString.substr(0, commaPos);
	dataString.erase(0,commaPos+1);


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