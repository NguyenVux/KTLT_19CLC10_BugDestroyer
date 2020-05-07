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
