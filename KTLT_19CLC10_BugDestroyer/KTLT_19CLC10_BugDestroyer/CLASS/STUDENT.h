#pragma once
#include "USER.h"
#include "CLASS.cpp"

class STUDENT :	public USER
{
private:
	std::string ClassID;
	linkedList<CLASS>* ClassList;
	linkedList<SCOREBOARD>* scoreboard;
public:
	void showMenu();
};

