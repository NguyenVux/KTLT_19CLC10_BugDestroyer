#pragma once
#include "USER.h"
#include "STUDENT.h"
class STAFF :
	public USER
{
private:
	linkedList<std::string>* ClasID;
	linkedList<CLASS>* Class;

	linkedList<std::string>* CourseID;
	linkedList<COURSE>* Course;

	linkedList<std::string>* StudentID;
	linkedList<STUDENT>* Student;
public:
	void showMenu();
};
