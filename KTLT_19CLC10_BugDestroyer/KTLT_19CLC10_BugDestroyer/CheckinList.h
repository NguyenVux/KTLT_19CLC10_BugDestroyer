#ifndef  _CHECKINLIST_H
#define _CHECKINLIST_H

#include <time.h>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

struct CheckinResult
{
	string CourseID;
	int result;
};
const string Results[3] = { "Absent","Checked","Late"};
class Checkin
{
public:
	static tm getCurrentTime();
};
#endif // ! _CHECKINLIST_H


