#ifndef _LECTURER_H
#define _LECTURER_H

#include "USER.h"
#include "STUDENT.h"
#include "SCOREBOARD.h"
#include <conio.h>
class Lecturer : public IUSER
{
private:
	string degree;

	linkedList<Course>* CourseList;
	linkedList<IUSER>* userList;
	linkedList<string>* MyCourseID;

	void showAllCourse();
	void showMyCourse();
	void viewCourseAttendances();
	void EditCourseAttendances();
	void viewScoreBoard();
public:
	Lecturer();
	int init(string dataString);
	void setUserList(linkedList<IUSER>* userList);
	void setCourseList(linkedList<Course>* Courselist);
	void showAdvanceMenu(int choice);
	string parse();
	void ViewInfo();
};
#endif

