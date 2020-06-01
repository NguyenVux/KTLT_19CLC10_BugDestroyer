#include "USER.h"



void IUSER::showBasicMenu(int choice)
{
	switch (choice)
	{
	case 0:
	{
		ViewInfo();
		break;
	}
	case 1:
	{
		bool retry = true;
		while (retry)
		{
			cout << "Please Enter your current password:";
			string currPass;
			cin >> currPass;
			cout << "Please Enter your new password:";
			string newPass;
			cin >> newPass;
			cout << "Please confirm password:";
			string confirmPass;
			cin >> confirmPass;
			int result = changePassword(currPass, newPass, confirmPass);
			if (result == 0)
			{
				cout << "Change Password Successfully" << endl;
				cin.ignore();
				cin.get();
				break;
			}
			else
			{
				ConsoleUI retryMenu(5);
				retryMenu.addLine("retry");
				retryMenu.addLine("back");
				int choice = 0;
				while (!retryMenu.getState() || choice != retryMenu.exitChoice())
				{
					retryMenu.clear();
					if (result == 1)
					{
						cout << "Your password and confirmation password do not match" << endl;
					}
					else if (result == 2)
					{
						cout << "Wrong password" << endl;

					}
					retryMenu.showMenu();
					retryMenu.getKey();
					if (retryMenu.getState())
					{
						choice = retryMenu.getChoice();
						if (choice == 0)
						{
							retry = true;
						}
						else
						{
							retry = false;
						}
					}
				}

			}
		}
		break;
	}
	default:
		break;
	}
}

int IUSER::getRole()
{
	return this->role;
}

void IUSER::ShowInfo()
{
	cout << "this is info";
}

int IUSER::changePassword(string oldPassword, string newPassword, string confirmNewPassword)
{
	if (this->password != oldPassword)
	{
		return 2;
	}
	if (newPassword != confirmNewPassword)
	{
		return 1;
	}
	this->password = newPassword;
	return 0;
}

bool IUSER::Authenticate(string id, string pw)
{
	if (id == this->ID && pw == this->password)
	{
		return true;
	}
	return false;
}

string IUSER::getID()
{
	return this->ID;
}

void IUSER::ViewInfo()
{
	cout << "ID: " << this->ID << endl;
	cout << "Name: " << this->name << endl;
	if (gender == MALE)
	{
		cout << "Gender: Male" << endl;
	}
	else
	{
		cout << "Gender: Female" << endl;
	}
	cout << "Day of Birth: " << this->DoB << endl;
	//system("pause");
}

string IUSER::getName()
{
	return this->name;
}
