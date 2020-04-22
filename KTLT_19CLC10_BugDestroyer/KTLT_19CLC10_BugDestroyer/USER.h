#pragma once
#include <string>
#include "LinkedList/linkedList.h"
#include "CLASS.h"
#include "COURSE.h"
#include "SCOREBOARD.h"

enum role
{
	staff,
	lecturer ,
	student
};

class USER
{
protected:
	std::string userName;
	std::string password;
	int role;
public:
	void init(std::string userName, std::string password);
	bool Authenticate(std::string password);
	bool ChangePassword(int role,std::string currentPassword,std::string newPassword);
	virtual void showMenu() = 0;
};
