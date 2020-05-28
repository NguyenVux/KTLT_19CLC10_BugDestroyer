#ifndef  _SCOREBOARD_H
#define _SCOREBOARD_H
#include <string>
#include <fstream>
#include <iostream>
#include "ioHelper.h"
#include "LinkedList/singly_linkedList.h"

struct ScoreRecord
{
	std::string studentID = "not found";
	float midTerm = 0;
	float final = 0;
	float lab = 0;
	float bonus = 0;
};
class SCOREBOARD
{
public:
	SCOREBOARD(std::string CourseID);
	~SCOREBOARD();
	ScoreRecord getByID(std::string studentID);
	ScoreRecord getCurrent();
	bool next();
	void ResetCursor();
private:
	
	std::string CourseID;
	linkedList<ScoreRecord>* ScoreRecords;
	node<ScoreRecord>* cursor;

};
#endif



