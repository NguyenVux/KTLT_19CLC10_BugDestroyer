#ifndef _LECTURER_H
#define _LECTURER_H

#include "USER.h"
class Lecturer : public IUSER
{
private:
	string degree;

	linkedList<Course>* CourseList;
	linkedList<IUSER>* userList;
	linkedList<string>* MyCourseID;
public:
	Lecturer();
	int init(string dataString);
	void setUserList(linkedList<IUSER>* userList);
	void setCourseList(linkedList<Course>* Courselist);
	void showMenu();
	string parse();
	void ViewInfo();
};
#endif

