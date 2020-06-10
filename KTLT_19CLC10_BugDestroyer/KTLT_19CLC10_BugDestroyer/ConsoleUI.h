#ifndef _CONSOLEUI_H
#define _CONSOLEUI_H
//#include "SinglyLinkedList.h"
#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <string>
using namespace std;
class ConsoleUI
{
private:
	string title;
	vector<string> MenuLines;
	const int LinePerPage;
	int page = 1;
	int CurrentPage = 1;
	int choice = 0;
	bool isEnter = false;
public:
	ConsoleUI(int linePerPage);
	void addTitle(string title);
	void addLine(string title);
	void removeLine(int index);
	int exitChoice();
	void getKey();
	void clear();
	bool getState();
	void showMenu();
	int getChoice();
	~ConsoleUI();
};
#endif

