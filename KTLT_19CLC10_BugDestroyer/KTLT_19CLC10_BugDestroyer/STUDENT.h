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

	// Vì đây là edit student nên tôi sẽ thêm hàm thay đổi thuộc tính của student;

	//Thay đổi tên
	void setName(string newName);
	//Đổi date of birth
	void setDoB(string newDoB);
	

	//giờ có 2 hàm thay đổi thông tin cơ bản của student, mình qua bên staff lại để thêm chức năng sửa student

};

