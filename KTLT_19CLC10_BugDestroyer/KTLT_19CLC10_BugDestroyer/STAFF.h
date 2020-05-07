#pragma once
#include "USER.h"
#include "Student.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
class Staff: public IUSER
{
public:
	void ViewInfo();
private:
	linkedList<IUSER>* userList=0;
	linkedList<Course>* Courselist=0;
	linkedList<CLASS>* ClassList=0;
	void showClass();
	void showCourse();
	void showStudent();
	void ImportClassFromFile();
	void importCourseFromFile();
public:
	Staff();
	void showMenu();
	int init(string dataString);
	void setUserList(linkedList<IUSER>* userList);
	void setCourseList(linkedList<Course>* Courselist);
	void setClassList(linkedList<CLASS>* ClassList);
	string parse();
};

