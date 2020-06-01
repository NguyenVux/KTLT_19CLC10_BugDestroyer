#include "ConsoleUI.h"

ConsoleUI::ConsoleUI(int linePerPage): LinePerPage (linePerPage)
{
}

void ConsoleUI::addLine(string title)
{
	MenuLines.push_back(title);
	page = MenuLines.size() / (LinePerPage) + 1;
}

void ConsoleUI::removeLine(int index)
{
	MenuLines.pop_back();
	page = MenuLines.size() / (LinePerPage)+1;
}

int ConsoleUI::exitChoice()
{
	return MenuLines.size()-1;
}

void ConsoleUI::getKey()
{
	int a = _getch();
	if (a == 224)
	{
		a = _getch();

		if (a == 72)
		{
			choice--;
		}
		if (a == 80)
		{
			choice++;
		}
		
	}
	else if(a == 13)
	{
		isEnter = true;
	}
	
	if (choice < 0)
	{
		choice += MenuLines.size();
	}
	else
	{
		choice = choice % MenuLines.size();
	}
	CurrentPage = (choice / LinePerPage)+1;
}

void ConsoleUI::clear()
{
	system("CLS");
}

bool ConsoleUI::getState()
{
	return isEnter;
}

void ConsoleUI::showMenu()
{
	isEnter = false;
	int NumberOfLine;
	if (CurrentPage < (page) ||MenuLines.size() % (LinePerPage) == 0)
	{
		NumberOfLine = LinePerPage;
	}
	else
	{
		NumberOfLine = MenuLines.size() % (LinePerPage);
	}
	for (int i = 0; i < NumberOfLine; i++)
	{
			if (choice == i+((CurrentPage-1)*(LinePerPage)))
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
			}
			string data = MenuLines[i + ((CurrentPage - 1) * LinePerPage)];
			cout << data << endl;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
	}
	cout << "----------------------------------------------------" << endl;
	cout << "Page" << CurrentPage << "/" << page << endl;
}

int ConsoleUI::getChoice()
{
	return choice;
}

ConsoleUI::~ConsoleUI()
{
}
