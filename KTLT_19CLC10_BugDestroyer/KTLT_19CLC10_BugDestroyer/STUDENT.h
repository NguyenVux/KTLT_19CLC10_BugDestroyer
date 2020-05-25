#pragma once
#include "USER.h"
class Student :
	public IUSER
{
public:
	void ViewInfo();
private:
	string ClassID ="";
	linkedList<string> *CourseID;
	linkedList<Course>* CourseList;
	void showEnrolledCourse();
	void showAllCourse();
	void viewSchedue();
public:
	Student();
	void showMenu();
	int init(string dataString);
	string parse();
	void addCourse(string courseID);
	void setCourseList(linkedList<Course> *courseList);

	// Vì đây là edit student nên tôi sẽ thêm hàm thay đổi thuộc tính của student;

	//Thay đổi tên
	void setName(string newName);
	//Đổi date of birth
	void setDoB(string newDoB);
	void ChangeClass(string ClassID);
	bool isEnrolled(string CourseID);
	~Student();

};

