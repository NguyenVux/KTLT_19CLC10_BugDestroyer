#pragma once
#include "USER.h"
class Lecturer :
	public USER
{
private:
	linkedList<std::string>* CourseID;
	linkedList<COURSE>* Course;

	linkedList<std::string>* StudentID;
	linkedList<STUDENT>* Student;
public:
};

