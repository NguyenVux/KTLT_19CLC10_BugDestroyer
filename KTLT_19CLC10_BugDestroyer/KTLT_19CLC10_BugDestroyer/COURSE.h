#ifndef _COURSE_H
#define _COURSE_H
#include <string>
#include "typeConverter.h"
#include <iostream>

using namespace converter;
using namespace std;
struct Date
{
	int year;
	int month;
	int day;
	
};
Date StringToDate(string input);
struct Time
{
	int hour;
	int minute;
};
Time StringToTime(string input);
enum DAY_OF_WEEK
{
	 Mon, Tue, Wed, Thur, Fri, Sat, Sun
};

class Course
{
public:
	string ID;
	string ClassID;
	string courseName;
	string lecturerID;
	Date startDate;
	Date endDate;
	int dayOfweek;
	Time startTime;
	Time endTime;
	string room;
	Course(string dataString);
	string parse();
	void viewInfo();
};
#endif

