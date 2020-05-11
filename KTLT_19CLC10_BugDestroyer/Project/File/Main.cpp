#include "Header.h"



int main() {
	Student s;
	ifstream f1;
	vector<Student>list_student;
	f1.open("Project.csv");

	if (!f1.is_open()) {
		cout << "Can not open file" << endl;
	}
	else {
		string ignore_line = "";
		getline(f1, ignore_line);
		load(f1, s, list_student);

		ofstream f2;
		f2.open("Schedule.txt");
		if (!f2.is_open()) {
			cout << "Can not create file" << endl;
		}
		else {
			save(f2, list_student);

			f2.close();
		}
		cout << list_student.size();

		f1.close();
	
	return 0;
}


