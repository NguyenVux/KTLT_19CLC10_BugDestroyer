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
enum gender
{
	male,
	female
};

class USER
{
protected:
	std::string userName;
	std::string password;
	int role;
	int Gender;
public:
	void init(std::string userName, std::string password);
	bool Authenticate(std::string password);
	bool ChangePassword(int role,std::string currentPassword,std::string newPassword);
	virtual void showMenu() = 0;
};
