#include "functions.h"









int main()
{
	linkedList<Course>* courseList = loadCourse();
	linkedList<CLASS>* ClassList = loadClass();
	linkedList<IUSER>* userList = LoadUser(courseList,ClassList);
 	IUSER* Session = 0;
	ConsoleUI Menu[3] = { ConsoleUI(10),ConsoleUI(10),ConsoleUI(10) };
	ConsoleUI BasicMenu(5);
	ConsoleUI LoginMenu(5);
	CreateUI(Menu);
	CreateBasicMenu(BasicMenu);
	CreateLoginMenu(LoginMenu);
	int LoginChoice = -1;
	

	while (!LoginMenu.getState() || LoginChoice != LoginMenu.exitChoice())
	{
		if (Session == 0)
		{
			LoginMenu.clear();
			LoginMenu.showMenu();
			LoginMenu.getKey();
			if (LoginMenu.getState())
			{
				LoginChoice = LoginMenu.getChoice();
				if (LoginChoice == 0)
				{
					Session = login(userList);
				}
			}
		}
		else
		{
			int choice = 0;
			while (!BasicMenu.getState() || choice != BasicMenu.exitChoice())
			{
				BasicMenu.clear();
				BasicMenu.showMenu();
				BasicMenu.getKey();
				if (BasicMenu.getState())
				{
					choice = BasicMenu.getChoice();
					if (choice < 2)
					{
						Session->showBasicMenu(choice);
					}
					else if(choice == 2)
					{ 
						int SessionRole = Session->getRole();
						choice = 0;
						while (!Menu[SessionRole].getState() || choice != Menu[SessionRole].exitChoice())
						{
							Menu[SessionRole].clear();
							Menu[SessionRole].showMenu();
							Menu[SessionRole].getKey();
							if (Menu[SessionRole].getState())
							{
								choice = Menu[SessionRole].getChoice();
								Session->showAdvanceMenu(choice);
							}
						}
					}
				}
			}
			Session = 0;
			LoginChoice = 0;
		}
	}
	updateUser(userList);
	updateCourse(courseList);
	delete userList, courseList, ClassList;
	return 0;
}