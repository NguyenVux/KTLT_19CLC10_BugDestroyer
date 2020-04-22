
#include "USER.h"

USER::USER(std::string userName, std::string password)
{
	this->userName = userName;
	this->password = password;
}

bool USER::Authenticate(std::string password)
{
	if (this->password == password)
	{
		return true;
	}
	else
	{
		return false;
	}
}