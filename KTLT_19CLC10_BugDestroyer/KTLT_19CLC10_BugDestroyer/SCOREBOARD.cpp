#include "SCOREBOARD.h"

SCOREBOARD::SCOREBOARD(std::string CourseID)
{
	//test binary file for more secure
	this->CourseID = CourseID;
	ScoreRecords = new linkedList<ScoreRecord>;
	std::ifstream file;
	file.open("Data\\scoreboard\\" + CourseID + ".txt");
	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string buffer;
			getline(file, buffer);
			node<ScoreRecord>* recordNode = new node<ScoreRecord>;
			recordNode->data = new ScoreRecord;
			recordNode->data->studentID;
			
			int commaPos = buffer.find(',');
			recordNode->data->studentID = buffer.substr(0, commaPos);
			buffer.erase(0, commaPos + 1);

			commaPos = buffer.find(',');
			recordNode->data->midTerm = stof(buffer.substr(0, commaPos));
			buffer.erase(0, commaPos + 1);

			commaPos = buffer.find(',');
			recordNode->data->final= stof(buffer.substr(0, commaPos));
			buffer.erase(0, commaPos + 1);

			commaPos = buffer.find(',');
			recordNode->data->lab = stof(buffer.substr(0, commaPos));
			buffer.erase(0, commaPos + 1);

			commaPos = buffer.find(',');
			recordNode->data->bonus = stof(buffer.substr(0, commaPos));
			buffer.erase(0, commaPos + 1);
			ScoreRecords->insert(recordNode);
		}
	}
	ResetCursor();
}

SCOREBOARD::~SCOREBOARD()
{
	delete ScoreRecords;
}

ScoreRecord SCOREBOARD::getByID(std::string studentID)
{
	node<ScoreRecord>* currRecord = ScoreRecords->head;
	while (currRecord)
	{
		if (currRecord->data->studentID == studentID)
		{
			return *(currRecord->data);
		}
		currRecord = currRecord->next;
	}
	return ScoreRecord();
}

ScoreRecord SCOREBOARD::getCurrent()
{
	return *(cursor->data);
}

bool SCOREBOARD::next()
{
	if (!cursor->next)
	{
		return false;
	}
	else
	{
		cursor = cursor->next;
		return true;
	}
}

void SCOREBOARD::ResetCursor()
{
	cursor = ScoreRecords->head;
}

