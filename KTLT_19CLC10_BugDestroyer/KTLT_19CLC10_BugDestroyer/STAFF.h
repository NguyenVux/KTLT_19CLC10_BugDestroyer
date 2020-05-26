#pragma once
#include "USER.h"
#include "Student.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
class Staff: public IUSER
{
public:
	void ViewInfo();
private:
	linkedList<IUSER>* userList=0; //danh sách user
	linkedList<Course>* Courselist = 0;
	linkedList<CLASS>* ClassList=0;
	void showClass(); //Chức năng Số 11cm
	void showCourse(); //Chức Năng số 12
	void showStudent(string Class); // Chức năng mở rộng
	void ImportClassFromFile();//chức năng số 6
	void importCourseFromFile();// chức na8g số 14
	void change_student_class(string ClassID, string StudentId);
	//tạo chức năng sửa student
	//mình nhận vào hàm một studentID để edit
	void editStudent(string StudentID);
	void addStudent();
	bool checkDupID(string ID);
	void addCourse();
public:
	Staff();
	void showMenu();
	int init(string dataString);
	void setUserList(linkedList<IUSER>* userList);
	void setCourseList(linkedList<Course>* Courselist);
	void setClassList(linkedList<CLASS>* ClassList);
	void removeStudent(string studentID);
	string parse();
	static string monthConverter(int month);
};

