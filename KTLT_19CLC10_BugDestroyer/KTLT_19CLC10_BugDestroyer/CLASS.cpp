#include "CLASS.h"

CLASS::CLASS(string dataString)
{
	this->CourseID = new linkedList<string>;
	int commaPos = dataString.find(',');
	this->classID = dataString.substr(0,commaPos);
	dataString.erase(0,commaPos+1);
	while (dataString.find(',') != string::npos)
	{
		node<string>* CourseIdNode = new node <string>;
		CourseIdNode->data = new string;
		commaPos = dataString.find(',');
		*(CourseIdNode->data) = dataString.substr(0, commaPos);
		dataString.erase(0, commaPos + 1);
		this->CourseID->insertTop(CourseIdNode);
	}
	node<string>* CourseIdNode = new node <string>;
	CourseIdNode->data = new string;
	commaPos = dataString.find(',');
	*(CourseIdNode->data) = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);
	this->CourseID->insertTop(CourseIdNode);


}

void CLASS::viewInfo()
{

}

void CLASS::viewClassInfo()
{
	cout <<"Class ID:"<< classID << endl;
	node<string>* tmp = this->CourseID->head;
	while (tmp != 0)
	{
		cout << "Course ID:" <<  *(tmp->data) << endl;
		tmp = tmp->next;
	}
}

linkedList<string> *CLASS::getCourse()
{
	return this->CourseID;
}

string CLASS::getClassID()
{
	return this->classID;
}

linkedList<CLASS>* loadClass()
{
	cout << "Loading Class List" << endl;
	linkedList<CLASS>* ClassList = new linkedList<CLASS>;
	fstream* file = new fstream;
	file->open("Data\\class.txt", ios::in);
	if (file->is_open())
	{
		string buffer;
		while (!file->eof())
		{
			char input;
			*file >> input;
			if (input != '#')
			{
				getline(*file, buffer);
				//cout << buffer;
				node<CLASS>* Class = new node<CLASS>;
				Class->data = new CLASS(input + buffer);
				ClassList->insert(Class);
			}
			else
			{
				file->ignore(1000, '\n');
			}
		}
	}
	else
	{
		cout << "class.txt not found" << endl;
		delete ClassList;
		delete file;
		return nullptr;
	}
	file->close();
	delete file;
	cout << "Fisnish Loading Class";
	system("cls");
	return ClassList;
}