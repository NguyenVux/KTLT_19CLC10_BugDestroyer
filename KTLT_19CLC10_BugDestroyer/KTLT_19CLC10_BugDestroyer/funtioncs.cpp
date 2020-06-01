#include "functions.h"

linkedList<IUSER>* LoadUser(linkedList<Course>* CourseList, linkedList<CLASS>* classList)
{
	cout << "Loading user list" << endl;
	linkedList<IUSER>* userlist = new linkedList<IUSER>;
	fstream* file = new fstream;
	string fileName = "user.txt";
	file->open(DataPath + fileName, ios::in);
	if (file->is_open())
	{
		while (!file->eof())
		{
			char input;
			*file >> input;
			if (input != '#')
			{
				if (charToInt(input) == STAFF)
				{
					file->ignore(1); // Skip Space seperator in user.txt  "role ID"
					string buffer;
					getline(*file, buffer);
					node<IUSER>* userInstance = new node<IUSER>;
					userInstance->data = new Staff;
					userInstance->data->init(buffer);
					Staff* staff_ptr = dynamic_cast<Staff*>(userInstance->data);
					if (staff_ptr != 0)
					{
						staff_ptr->setUserList(userlist);
						staff_ptr->setCourseList(CourseList);
						staff_ptr->setClassList(classList);
					}

					userlist->insert(userInstance);
				}
				if (charToInt(input) == STUDENT)
				{
					file->ignore(1); // Skip Space seperator in user.txt  "role ID"
					string buffer;
					getline(*file, buffer);
					node<IUSER>* userInstance = new node<IUSER>;
					userInstance->data = new Student;
					userInstance->data->init(buffer);
					Student* StudentPtr = dynamic_cast<Student*>(userInstance->data);
					if (StudentPtr != 0)
					{
						StudentPtr->setCourseList(CourseList);
					}
					userlist->insert(userInstance);
				}
				if (charToInt(input) == LECTURER)
				{
					file->ignore(1); // Skip Space seperator in user.txt  "role ID"
					string buffer;
					getline(*file, buffer);
					node<IUSER>* userInstance = new node<IUSER>;
					userInstance->data = new Lecturer;
					userInstance->data->init(buffer);
					Lecturer* LecturerPtr = dynamic_cast<Lecturer*>(userInstance->data);
					if (LecturerPtr != 0)
					{
						LecturerPtr->setCourseList(CourseList);
						LecturerPtr->setUserList(userlist);
					}
					userlist->insert(userInstance);
				}

			}
			else
			{
				file->ignore(1000, '\n');
			}
		}
	}
	else
	{
		cout << "user.txt not found " << endl;
		delete file;
		delete userlist;
		return nullptr;
	}
	file->close();
	delete file;
	cout << "Fisnish Loading Course";
	system("cls");
	return userlist;
}

IUSER* login(linkedList<IUSER>* USER)
{
	system("cls");
	if (USER != nullptr)
	{

		string ID;
		string password;
		cout << "ID:";
		cin >> ID;
		cout << "Password: ";
		int buffer;
		do
		{

			buffer = _getch();
			if (buffer != 13)
			{
				//cout << password.length();
				if (buffer == 8 && password.length() > 0)
				{
					password.pop_back();
					cout << "\b \b";
				}
				else
				{
					if (buffer > 31 && buffer < 127)
					{
						cout << "*";
						password += char(buffer);
					}
				}
			}
		} while (buffer != 13);
		node<IUSER>* current = USER->head;
		if (ID == "exit")
		{
			return 0;
		}
		while (current != 0)
		{
			if (current->data->Authenticate(ID, password))
			{
				ioHelper::textGreen();
				cout << endl << "Login Success" << endl;
				ioHelper::blackLine();
				cout << "directing to main menu" << endl;
				Sleep(1500);
				return current->data;
			}
			current = current->next;

		}
		ioHelper::textRed();
		cout << endl << "Invalid ID or password" << endl;
		ioHelper::blackLine();
		system("pause");
		return 0;
	}
	return 0;
}

void updateUser(linkedList<IUSER>* userList)
{
	node<IUSER>* userNode = userList->head;
	fstream* file = new fstream;
	string fileName = "user.txt";
	file->open(DataPath + fileName, ios::out);
	*file << "#role id,password,name,gender,dob";
	while (userNode)
	{
		if (userNode->data != 0)
		{
			*file << endl << userNode->data->parse();
		}
		userNode = userNode->next;
	}
	file->close();
	delete file;
}






void CreateUI(ConsoleUI UI[3])
{
	UI[STUDENT].addLine("");

	UI[STAFF].addLine("Import Class");
	UI[STAFF].addLine("Manual Add Student");
	UI[STAFF].addLine("Edit Student");
	UI[STAFF].addLine("Remove Student");
	UI[STAFF].addLine("Change Student Class");
	UI[STAFF].addLine("View Class List");
	UI[STAFF].addLine("View Students of class");
	UI[STAFF].addLine("Import Course");
	UI[STAFF].addLine("Manual Add Course");
	UI[STAFF].addLine("Edit Course");
	UI[STAFF].addLine("Remove Course");
	UI[STAFF].addLine("Remove Student from Course");
	UI[STAFF].addLine("Add Student to Course");
	UI[STAFF].addLine("View Students of Course");
	UI[STAFF].addLine("View Course List");
	UI[STAFF].addLine("Back");

	UI[LECTURER].addLine("TEST");

}

void CreateLoginMenu(ConsoleUI& LoginMenu)
{
	LoginMenu.addLine("Login");
	LoginMenu.addLine("Exit");
}

void CreateBasicMenu(ConsoleUI& BasicMenu)
{
	BasicMenu.addLine("Show Info");
	BasicMenu.addLine("Change Password");
	BasicMenu.addLine("Advance Menu");
	BasicMenu.addLine("Exit");
}

