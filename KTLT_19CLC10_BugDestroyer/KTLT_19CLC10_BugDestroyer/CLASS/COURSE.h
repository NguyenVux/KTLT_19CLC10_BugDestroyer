#pragma once
#include <string>
#include "USER.h"
#include "STUDENT.h"
#include "SEMESTER.h"
enum DayOfWeek
{
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

const std::string DayOfWeek[7] = { "Monday","Tuesday","Wednesday","Thursday","Friday","Saturday","Sunday" };

class COURSE
{
private:
	std::string CourseID;
	std::string CourseName;
	std::string LecturerID;
	std::string startDate;
	std::string endDate;
	
	int dayOfWeek;
	std::string startTime;
	std::string endTime;
	SEMESTER semester;
	
	linkedList<USER> *userList;
public:
	COURSE(std::string id);
	std::string getCourse();
};

