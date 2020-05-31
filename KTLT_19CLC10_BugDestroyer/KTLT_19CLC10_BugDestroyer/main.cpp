#include "functions.h"









int main()
{
	linkedList<Course>* courseList = loadCourse();
	linkedList<CLASS>* ClassList = loadClass();
	linkedList<IUSER>* userList = LoadUser(courseList,ClassList);
 	IUSER* Session = 0;
	ConsoleUI Menu[3] = { ConsoleUI(10),ConsoleUI(10),ConsoleUI(10) };
	CreateUI(Menu);
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
			int choice = 0;
			ConsoleUI *MenuPtr = &Menu[Session->getRole()];
			while (!MenuPtr->getState() || choice != MenuPtr->exitChoice())
			{
				MenuPtr->clear();
				MenuPtr->showMenu();
				MenuPtr->getKey();
				if (Menu->getState())
				{
					choice = MenuPtr->getChoice();
					Session->showMenu(choice);
				}
				
			}
			Session = 0;
			choice = 0;
		}
	}
	updateUser(userList);
	delete userList,courseList;
	return 0;
}