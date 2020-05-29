#pragma once
#include "USER.h"
#include "ioHelper.h"
#include "SCOREBOARD.h"
#include "CheckinList.h"
#include <iomanip>
class Student :
	public IUSER
{
public:
	void ViewInfo();
private:
	string ClassID ="";
	linkedList<string> *CourseID;
	linkedList<Course>* CourseList = nullptr;
	void showEnrolledCourse();
	void showAllCourse();
	void showSchedue();
	void ShowScoreBoard();
	void checkin();
	void showCheckin();
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
	void setDoB(string newDoB);
	void ChangeClass(string ClassID);
	string getClassID();
	bool isEnrolled(string CourseID);
	void removeCourse(string courseName);
	~Student();


};

