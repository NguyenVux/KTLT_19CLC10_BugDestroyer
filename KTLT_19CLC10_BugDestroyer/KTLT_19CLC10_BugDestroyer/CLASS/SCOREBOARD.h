#pragma once

struct SCOREBOARD_ROW
{
	std::string StudentID;
	double MidTerm;
	double Final;
	double Bonus;
	double Total;
};
class SCOREBOARD
{
public:
	std::string courseID;
	linkedList<SCOREBOARD_ROW> row;


};

