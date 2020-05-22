#include <iostream>
#include <fstream>
#include <conio.h>
#include <filesystem>
#include <ctime>
#include "USER.h"
#include "STAFF.h""
#include "Student.h"
#include "CLASS.h"
#include "LinkedList/linkedList.h"


const char DataPath[] = "Data\\";

linkedList<CLASS>* loadClass()
{
	linkedList<CLASS>* ClassList = new linkedList<CLASS>;
	fstream* file = new fstream;
	string fileName = "class.txt";
	file->open(DataPath + fileName, ios::in);
	if (file->is_open())
	{
		string buffer;
		while (!file->eof())
		{
			char input;
			*file >> input;
			if (input != '#')
			{
				getline(*file, buffer);
				//cout << buffer;
				node<CLASS>* Class = new node<CLASS>;
				Class->data = new CLASS(input + buffer);
				ClassList->insertTop(Class);
			}
			else
			{
				file->ignore(1000, '\n');
			}
		}
	}
	else
	{
		cout << "class.txt not found" << endl;
		delete ClassList;
		delete file;
		return nullptr;
	}
	file->close();
	delete file;
	return ClassList;
}

linkedList<Course>* loadCourse()
{
	linkedList<Course>* courseList = new linkedList<Course>;
	fstream* file = new fstream;
	string fileName = "course.txt";
	file->open(DataPath + fileName, ios::in);
	if (file->is_open())
	{
		string buffer;
		while (!file->eof())
		{
			char input;
			*file >> input;
			if (input != '#')
			{
				getline(*file, buffer);
				node<Course>* course = new node<Course>;
				course->data = new Course(input+buffer);
				courseList->insertTop(course);
			}
			else
			{
				file->ignore(1000, '\n');
			}
		}
	}
	else
	{
		cout << "Course.txt not found" << endl;
		delete courseList;
		delete file;
		return nullptr;
	}
	file->close();
	delete file;
	return courseList;
}

linkedList<IUSER>* LoadUser(linkedList<Course>* CourseList, linkedList<CLASS>* classList)
{
	linkedList<IUSER>* userlist = new linkedList<IUSER>;
	fstream* file = new fstream;
	string fileName = "user.txt";
	file->open(DataPath+fileName, ios::in);
	if (file->is_open())
	{
		while (!file->eof())
		{
			char input;
			*file >> input;
			if (input != '#')
			{
				if(charToInt(input) == STAFF)
				{
					file->ignore(1); // Skip Space seperator in user.txt  "1 asd"
					string buffer;
					getline(*file, buffer);
					//cout <<endl<< buffer << endl;
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
					//cout << staff_ptr->parse() << endl;
					
					userlist->insertTop(userInstance);
				}	
				if (charToInt(input) == STUDENT)
				{
					file->ignore(1); // Skip Space seperator in user.txt  "1 asd"
					string buffer;
					getline(*file, buffer);
					node<IUSER>* userInstance = new node<IUSER>;
					userInstance->data = new Student;
					userInstance->data->init(buffer);
					Student* staff_ptr = dynamic_cast<Student*>(userInstance->data);
					if (staff_ptr != 0)
					{
						staff_ptr->setCourseList(CourseList);
					}
					userlist->insertTop(userInstance);
				}

			}
			else
			{
				file->ignore(1000,'\n');
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
	return userlist;
}

IUSER* login(linkedList<IUSER> *USER)
{
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
				if (buffer == 8 && password.length() >0)
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
		cout << endl << password;
		node<IUSER>* current = USER->head;
		if (ID == "exit")
		{
			return 0;
		}
		while (current != 0)
		{
			if (current->data->Authenticate(ID, password))
			{
				return current->data;
			}
			current = current->next;

		}
		cout << "Invalid ID or password" << endl;
		system("pause");
		return 0;
	}
	return 0;
}
void updateUser(linkedList<IUSER>* userList)
{
	node<IUSER>* userNode = userList->head;
	fstream* file = new fstream;
	file->open("user.txt", ios::out);
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
int main()
{
	linkedList<Course>* courseList = loadCourse();
	linkedList<CLASS>* ClassList = loadClass();
	linkedList<IUSER>* userList = LoadUser(courseList,ClassList);
 	IUSER* Session = 0;
	int choice = -1;
	
	while (choice != 2)
	{
		if (Session == 0)
		{
			system("cls");
			cout << "1.Login" << endl;
			cout << "2.Exit" << endl;
			cin >> choice;
			cin.clear();
			cin.ignore(100, '\n');
			if (choice == 1)
			{
				Session = login(userList);
			}
		}
		else
		{
			Session->showMenu();
			Session = 0;
		}
	}
	updateUser(userList);
	delete userList,courseList;
	return 0;
}