#pragma once
#include <string>
#include "LinkedList/linkedList.h"

class USER
{
protected:
	std::string userName;
	std::string password;
public:
	USER(std::string userName, std::string password);
	bool Authenticate(std::string password);
};
