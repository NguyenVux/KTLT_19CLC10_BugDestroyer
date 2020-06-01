#ifndef  _USER_h
#define _USER_h
#include <string>
#include <iostream>
#include "LinkedList/linkedList.h"
#include "COURSE.h"
#include "CLASS.h"
#include "typeConverter.h"
#include "ConsoleUI.h"
using namespace std;
using namespace converter;

enum role
{
	STAFF,
	STUDENT,
	LECTURER
};
enum gender
{
	MALE,
	FEMALE
};

class IUSER
{
protected:
	string ID;
	string password;
	string name;
	string DoB; // day of birth
	int gender;
	int role;
public:
	virtual void showAdvanceMenu(int choice) = 0;
	void showBasicMenu(int choice);
	virtual int init(string dataString) = 0;
	virtual string parse() = 0;
	int getRole();
	void ShowInfo();
	int changePassword(string oldPassword,string newPassword,string confirmNewPassword);
	bool Authenticate(string ID, string password);
	string getID();
	virtual void ViewInfo();
	string getName();
	void setPassword(string password);
	void setGender(int gender);
};


#endif

