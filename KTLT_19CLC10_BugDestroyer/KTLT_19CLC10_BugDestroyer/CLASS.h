#pragma once
#include <string>
#include "LinkedList/linkedList.h"
#include "USER.h"
#include <iostream>
using namespace std;
class CLASS
{
private:
	string classID;
	linkedList<string> *CourseID;
public:
	CLASS(string dataString);
	void viewInfo();
	void viewClassInfo();
	linkedList<string> *getCourse();
	string getClassID();
};


