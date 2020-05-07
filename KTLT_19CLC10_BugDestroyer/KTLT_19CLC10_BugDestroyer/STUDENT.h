#pragma once
#include "USER.h"
class Student :
	public IUSER
{
public:
	void ViewInfo();
private:
	string ClassID ="";
	linkedList<string> CourseID;
	linkedList<Course>* CourseList;
	void showEnrolledCourse();
	void showAllCourse();
public:
	Student();
	void showMenu();
	int init(string dataString);
	string parse();
	void addCourse(string courseID);
	void setCourseList(linkedList<Course> *courseList);
};

