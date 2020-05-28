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
class Checkin
{
public:
	static tm getCurrentTime();
};
#endif // ! _CHECKINLIST_H


