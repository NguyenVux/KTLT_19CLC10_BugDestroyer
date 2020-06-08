#ifndef  _SCOREBOARD_H
#define _SCOREBOARD_H
#include <string>
#include <fstream>
#include <iostream>
#include "ioHelper.h"
#include "LinkedList/singly_linkedList.h"

enum MODE
{
	IMPORT,
	READ
};

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
	SCOREBOARD(std::string CourseID, MODE mode = READ);
	~SCOREBOARD();
	ScoreRecord getByID(std::string studentID);
	ScoreRecord getCurrent();
	bool next();
	void ResetCursor();
	void exportScoreBoard();
private:
	void save();
	std::string CourseID;
	linkedList<ScoreRecord>* ScoreRecords;
	node<ScoreRecord>* cursor;

};
#endif



