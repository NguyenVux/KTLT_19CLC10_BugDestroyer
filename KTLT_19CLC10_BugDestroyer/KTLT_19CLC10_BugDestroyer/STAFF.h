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
	void showAdvanceMenu(int choice);
	int init(string dataString);
	void setUserList(linkedList<IUSER>* userList);
	void setCourseList(linkedList<Course>* Courselist);
	void setClassList(linkedList<CLASS>* ClassList);
	void removeStudent(string studentID);
	string parse();
	static string monthConverter(int month, int mode);
	/*
	mode 1: short month example: nov, may, sep
	mode 2: full month example: november, may, september
	*/
	bool checkDateInput(int day, int month, int year);
	string getDate(int day, int month, int year, int type);
	//note
	/*
	getDate note:
	type 1: DD/MM/YYYY
	type 2: DD-MM-YYYY
	type 3: American english date with short date
	Example: Apr 14th 2019
	type 4: British english date with short date
	Example: 14th April 2019
	type 5: American english date with full month
	Example: April 14th 2019
	type 6: British english date with full month
	Example: 14th April 2019
	*/
};

