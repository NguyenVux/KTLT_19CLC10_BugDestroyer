#pragma once
#include "USER.h"
#include "ioHelper.h"
#include "SCOREBOARD.h"
#include "CheckinList.h"
#include "LinkedList/ExtendableArray.h"
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
	
	void showSchedue();
	void showAllCourse();
	void ShowScoreBoard();
	void checkin();
	void showCheckin();
	static void CreateCheckinFile(string ID);
public:
	Student();
	void showAdvanceMenu(int choice);
	int init(string dataString);
	string parse();
	void addCourse(string courseID);
	void setCourseList(linkedList<Course> *courseList);
	void showEnrolledCourse();	
	//Thay đổi tên
	void setName(string newName);
	void setDoB(string newDoB);
	void ChangeClass(string ClassID);
	string getClassID();
	bool isEnrolled(string CourseID);
	void removeCourse(string courseName);
	~Student();


};

