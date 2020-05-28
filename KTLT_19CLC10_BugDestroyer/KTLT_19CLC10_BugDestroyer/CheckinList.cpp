#include "CheckinList.h"

tm Checkin::getCurrentTime()
{
	time_t now = time(0);
	tm currentTime;
	localtime_s(&currentTime, &now);

	return (currentTime);
}
