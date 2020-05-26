#include "STAFF.h"

void Staff::ViewInfo()
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
	system("pause");
}

void Staff::showCourse()
{
	node<Course>* current = this->Courselist->head;
	while (current != 0)
	{
		current->data->viewInfo();
		current = current->next;
	}
}

void Staff::showStudent(string Class)
{
	bool valid = false;
	node<IUSER>* cur = userList->head;
	while (cur) {
		if (cur->data->getRole() == 1) {
			Student* ptrStudent = dynamic_cast<Student*>(cur->data);
			if (ptrStudent->getClassID() == Class) ptrStudent->ViewInfo();
			cout << endl;
			valid = true;
		}
		cur = cur->next;
	}
	if (valid == false) cout << "Invalid class !" << endl;
}

void Staff::showClass()
{
	node<CLASS>* current = this->ClassList->head;
	while (current != 0)
	{
		current->data->viewClassInfo();
		current = current->next;
	}
	system("pause");
}

void Staff::ImportClassFromFile()
{
	cout << "Please Place the file in Import folder and  press Enter to continue" << endl;
	cin.ignore();
	cin.get();
	cout << "Enter your class: ";
	string fileName;
	cin >> fileName;
	fstream* file = new fstream;
	file->open("import\\" + fileName + ".csv", ios::in);
	if (file->is_open())
	{
		linkedList<IUSER>* tmpUserList = new linkedList<IUSER>;
		while (!file->eof())
		{
			string buffer;
			getline(*file, buffer);
			cout << buffer << endl;
			node<IUSER>* userInstance = new node<IUSER>;
			userInstance->data = new Student;
			userInstance->data->init(buffer + "," + fileName);
			node<IUSER>* tmp = this->userList->head;
			while (tmp != 0)
			{
				if (tmp->data->getID() == userInstance->data->getID())
				{
					cout << "Dupliate ID with existed Student\n";
					tmp->data->ViewInfo();
					cout << "\nStop importing from " + fileName + ".csv" << endl;
					cout << "Import failed - Roll back all changes\npress Enter to continue " << endl;
					cin.ignore();
					cin.get();
					delete tmpUserList;
					return;
				}
				tmp = tmp->next;
			}
			node<CLASS>* ClassTmp = this->ClassList->head;
			Student* stuPtr = dynamic_cast<Student*> (userInstance->data);
			while (ClassTmp != 0)
			{
				if (fileName == ClassTmp->data->getClassID())
				{
					if (stuPtr != 0)
					{
						linkedList<string>* CourseIDList = ClassTmp->data->getCourse();
						node<string>* CourseIDtmp = CourseIDList->head;
						while (CourseIDtmp != 0)
						{
							stuPtr->addCourse(*(CourseIDtmp->data));
							CourseIDtmp = CourseIDtmp->next;
						}
					}
				}
				ClassTmp = ClassTmp->next;
			}
			stuPtr->setCourseList(this->Courselist);
			tmpUserList->insertTop(userInstance);
		}
		this->userList->head = linkedList<IUSER>::joinList(tmpUserList, this->userList);
		cout << "Import finished \npress Enter to continue " << endl;
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "File Not found, press AnyKey to continue" << endl;
		cin.ignore();
		cin.get();
	}
	file->close();
	delete file;
}

void Staff::importCourseFromFile()
{
	cout << "Please Place the file in Import folder and  press Enter to continue" << endl;
	cin.ignore();
	cin.get();
	cout << "Enter your File (csv file): ";
	string fileName;
	cin >> fileName;
	fstream* file = new fstream;
	file->open("import\\" + fileName + ".csv", ios::in);

	if (file->is_open())
	{
		linkedList<Course>* tempCourseList = new linkedList<Course>;
		while (!file->eof())
		{

			string buffer;
			getline(*file, buffer);
			cout << buffer << endl;
			node<Course>* courseInstance = new node<Course>;
			courseInstance->data = new Course(buffer);
			node<Course>* tmp = this->Courselist->head;
			while (tmp != 0)
			{
				if (tmp->data->ID == courseInstance->data->ID)
				{
					cout << "Dupliate ID with existed Course\n";
					tmp->data->viewInfo();
					cout << "\nStop importing from " + fileName + ".csv" << endl;
					cout << "Import failed - Roll back all changes\npress Enter to continue " << endl;
					cin.ignore();
					cin.get();
					delete tempCourseList;
					return;
				}
				tmp = tmp->next;
			}
			tempCourseList->insertTop(courseInstance);
		}
		this->Courselist->head = linkedList<Course>::joinList(tempCourseList, this->Courselist);
		cout << "Import finished \npress Enter to continue " << endl;
		cin.ignore();
		cin.get();
	}
	else
	{
		cout << "File Not found, press AnyKey to continue" << endl;
		cin.ignore();
		cin.get();
	}
	file->close();
	delete file;
}

void Staff::editStudent(string StudentID)
{
	node<IUSER>* CurrentStudent = userList->head;
	//ở đây tôi xài kế thừa, nên class cha là IUSER
	while (CurrentStudent != 0)
	{
		//kiểm ra người dùng có phải là student ko
		//dùng hàm getRole viết sẵn để lấy Role của User
		if (CurrentStudent->data->getRole() == STUDENT)
		{
			// à quên còn so sánh studentID
			if (CurrentStudent->data->getID() == StudentID)
			{

				//nếu người dùng là student tôi sẽ ép kiểu lại tại vì ko gọi hàm của student được từ class IUSER
				//tạo pointer là học sinh
				Student* ptrStudent = dynamic_cast<Student*>(CurrentStudent->data);
				//gọi hàm thay đổi tên
				ptrStudent->setName("New Name");
			}

		}
		CurrentStudent = CurrentStudent->next; // =)) quên nhẹ dòng này
	}
	//thế là xong chức năng đổi tên
}

Staff::Staff()
{
	this->role = STAFF;
}

void Staff::showMenu()
{
	int choice = -1;
	string StudentID, ClassID;
	while (choice != 0)
	{
		system("CLS");
		cout << "1.Personal Info" << endl;
		cout << "2.Show all Course" << endl;
		cout << "3.Import Course from file" << endl;
		cout << "4.Show all class" << endl;
		cout << "5.Import Class from file" << endl;
		cout << "6.Show all Student" << endl;
		cout << "7.Change Student Info" << endl;
		cout << "8.Remove student" << endl;
		cout << "9.Change student class" << endl;
		cout << "10.Add student" << endl;
		cout << "11.Show student in a class" << endl;
		cout << "12.Add new coure" << endl;
		cout << "0.Log out" << endl;
		cout << "enter your choice:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
			ViewInfo();
			break;
		case 2:
			showCourse();
			system("pause");
			break;
		case 3:
			importCourseFromFile();
			break;

		case 4:
			showClass();
			break;
		case 5:
			ImportClassFromFile();
			break;
		case 7:
			cout << "Input Student ID" << endl;
			cin.ignore();
			getline(cin, StudentID);
			editStudent(StudentID);
			//chạy thử
			break;
		case 8:
			cout << "Input Student ID" << endl;
			cin.ignore();
			getline(cin, StudentID);
			removeStudent(StudentID);
			break;
		case 9:
			cout << "Input Student ID" << endl;
			cin.ignore();
			getline(cin, StudentID);
			cout << "Input Class ID" << endl;
			getline(cin, ClassID);
			change_student_class(ClassID, StudentID);
			break;
		case 10:
			addStudent();
			break;
		case 11:
			cout << "enter ClassID: ";
			cin.ignore();
			getline(cin, ClassID);
			showStudent(ClassID);
			break;
		case 12:
			addCourse();
			break;
		default:
			cout << "PLease Enter The choice you want" << endl;
			break;
		}
	}
}


int Staff::init(string dataString)
{
	int commaPos = dataString.find(',');
	this->ID = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);


	commaPos = dataString.find(',');
	this->password = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	commaPos = dataString.find(',');
	this->name = dataString.substr(0, commaPos);
	dataString.erase(0, commaPos + 1);

	commaPos = dataString.find(',');
	this->gender = strToInt(dataString.substr(0, commaPos));
	dataString.erase(0, commaPos + 1);
	this->DoB = dataString;
	return 0;
}

void Staff::setCourseList(linkedList<Course>* Courselist)
{
	this->Courselist = Courselist;
}

void Staff::setClassList(linkedList<CLASS>* ClassList)
{
	this->ClassList = ClassList;
}

string Staff::parse()
{
	string parseResult = "0 " + this->ID + ',' + this->password + ',' + this->name + ',' + char(this->gender + 48) + ',' + this->DoB;
	return parseResult;
}

void Staff::setUserList(linkedList<IUSER>* UserList)
{
	this->userList = UserList;
}

void Staff::removeStudent(string studentID) {
	node<IUSER>* cur = userList->head;
	if (cur->data->getID() == studentID) {
		if (cur->data->getRole() == STUDENT) {
			userList->head = cur->next;
			delete cur;
			return;
		}
	}
	/*node<IUSER>* temp = cur;*/
	cur = cur->next;
	while (cur->next) {
		if (cur->next->data->getRole() == STUDENT) {
			if (cur->next->data->getID() == studentID)
			{
				node<IUSER>* tmp = cur;
				tmp->next = tmp->next->next;
				delete cur;
				return;
			}
		}
		cur = cur->next;
	}
}

void Staff::change_student_class(string ClassID, string StudentID) {
	node<IUSER>* cur = userList->head;
	while (cur != 0)
	{
		if (cur->data->getRole() == STUDENT)
		{
			if (cur->data->getID() == StudentID)
			{
				Student* ptrStudent = dynamic_cast<Student*>(cur->data);
				ptrStudent->ChangeClass(ClassID);
			}
		}
		cur = cur->next;
	}
}

void Staff::addStudent() {
	cout << "enter id: ";
	string id;
	cin.ignore();
	getline(cin, id);
	cout << checkDupID(id) << endl;
	if (checkDupID(id) == true) {
		cout << "the ID already exist!" << endl;
		system("pause");
		return;
	}
	else {
		cout << "enter name: "; string name;
		getline(cin, name);
		cout << "enter class: "; string which_class;
		getline(cin, which_class);
		int choice_gender = 5;
		while (choice_gender < 0 || choice_gender>1) {
			cout << "gender(0: male, 1: Female): ";
			cin >> choice_gender;
		}
		string gender;
		if (choice_gender == 0) gender = "0";
		else gender = "1";
		int tempY, tempM, tempD;
		bool check = false;
		bool leapYear = false;
		string day;
		string year;
		string month;
		cin.ignore();
		while (check == false) {
			cout << "Day of birth: " << endl;
			cout << "day: "; getline(cin, day);
			cout << "month: "; getline(cin, month);
			cout << "year: "; getline(cin, year);
			tempY = converter::strToInt(year);
			if ((tempY % 100) == 0) {
				if ((tempY % 400) == 0) leapYear = true;
			}
			else if ((tempY % 4) == 0) leapYear = true;
			tempM = converter::strToInt(month);
			if (tempM > 12 || tempM < 1) cout << "Invalid month input! (1 < month < 12)" << endl;
			else {
				tempD = converter::strToInt(day);
				if (tempM == 2) {
					if (leapYear == true) {
						if (tempD < 1 || tempD>29) cout << "Invalid day input! (1<day<29) (Feb) (leap year = true)" << endl;
						else check = true;
					}
					else {
						if (tempD < 1 || tempD>28) cout << "Invalid day input! (1<day<28) (Feb) (leap year = false)" << endl;
						else check = true;
					}
				}
				if (tempM == 1 || tempM == 3 || tempM == 5 || tempM == 7 || tempM == 8 || tempM == 10 || tempM == 12) {
					if (tempD < 1 || tempD>31) cout << "Invalid day input! (1<day<31) (" << monthConverter(tempM) << ")" << endl;
					else check = true;
				}
				if (tempM == 4 || tempM == 6 || tempM == 9 || tempM == 11) {
					if (tempD < 1 || tempD>30) cout << "Invalid day input (1<day<30) (" << monthConverter(tempM) << ")" << endl;
					else check = true;
				}
			}
		}
		string password = day + month + year;
		string dob = day + "-" + month + "-" + year;
		node<IUSER>* p = new node<IUSER>;
		p->data = new Student;
		p->data->init(id + "," + password + "," + name + "," + gender + "," + dob + "," + which_class);
		userList->insertTop(p);
	}
}

string Staff::monthConverter(int month) {
	string res;
	switch (month)
	{
	case 1: res = "Jan";
		break;
	case 2: res = "Feb";
		break;
	case 3: res = "Mar";
		break;
	case 4: res = "Apr";
		break;
	case 5: res = "May";
		break;
	case 6: res = "Jun";
		break;
	case 7: res = "Jul";
		break;
	case 8: res = "Aug";
		break;
	case 9: res = "Sep";
		break;
	case 10: res = "Oct";
		break;
	case 11: res = "Nov";
		break;
	case 12: res = "Dec";
		break;
	default:
		res = "Invalid month";
		break;
	}
	return res;
}

bool Staff::checkDupID(string ID) {
	node<IUSER>* cur = userList->head;
	while (cur) {
		if (cur->data->getID() == ID) return true;
		cur = cur->next;
	}
	return false;
}

void Staff::addCourse()
{
	cout << "Course ID:";
	string courseID;
	cin.ignore();
	getline(cin, courseID);
	if (checkDupID(courseID) == true) {
		cout << "the ID already exist!" << endl;
		system("pause");
		return;
	}
	else
	{
		cout << "Course Name:";
		string courseName;
		getline(cin, courseName);
		cout << "Lecturer Name:";
		string lecturerName;
		getline(cin, lecturerName);
		cout << "Class Name:";
		string className;
		getline(cin, className);
		cout << "Start Date:";
		string startDate;
		getline(cin, startDate);
		cout << "End Date:";
		string endDate;
		getline(cin, endDate);
		cout << "Start Hour:";
		string startHour;
		getline(cin, startHour);
		cout << "End hour:";
		string endHour;
		getline(cin, endHour);
		cout << "Room:";
		string room;
		getline(cin, room);
		node<Course>* p = new node<Course>;
		p->data = new Course(courseID + "," + courseName + "," + lecturerName + "," + className + "," + startDate + "," + endDate + "," + startHour + "," + endHour + "," + room);
		Courselist->insert(p);
	}


}

