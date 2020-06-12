#include "SCOREBOARD.h"

SCOREBOARD::SCOREBOARD(std::string CourseID,MODE mode)
{
	//test binary file for more secure
	if (mode == READ)
	{
		this->CourseID = CourseID;
		ScoreRecords = new linkedList<ScoreRecord>;
		std::ifstream file;
		file.open("Data\\scoreboard\\" + CourseID + ".txt");
		if (file.is_open())
		{
			std::string buffer;
			while (getline(file, buffer))
			{
				
				node<ScoreRecord>* recordNode = new node<ScoreRecord>;
				recordNode->data = new ScoreRecord;
				recordNode->data->studentID;

				size_t commaPos = buffer.find(',');
				recordNode->data->studentID = buffer.substr(0, commaPos);
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->midTerm = stof(buffer.substr(0, commaPos));
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->final = stof(buffer.substr(0, commaPos));
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->lab = stof(buffer.substr(0, commaPos));
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->bonus = stof(buffer.substr(0, commaPos));
				buffer.erase(0, commaPos + 1);
				ScoreRecords->insert(recordNode);
			}
			result = true;
		}
		else
		{
			cout << CourseID << " scoreboard is not found, please import scoreboard\n ";
			system("PAUSE");
		}
	}
	else if (mode == IMPORT)
	{
		this->CourseID = CourseID;
		ScoreRecords = new linkedList<ScoreRecord>;
		std::ifstream file;
		file.open("Import\\" + CourseID + ".csv");
		if (file.is_open())
		{
			std::string buffer;
			getline(file, buffer);
			while (getline(file, buffer))
			{			
				node<ScoreRecord>* recordNode = new node<ScoreRecord>;
				recordNode->data = new ScoreRecord;
				recordNode->data->studentID;
				size_t commaPos = buffer.find(',');
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->studentID = buffer.substr(0, commaPos);
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->midTerm = stof(buffer.substr(0, commaPos));
				buffer.erase(0, commaPos + 1);

				commaPos = buffer.find(',');
				recordNode->data->final = stof(buffer.substr(0, commaPos));
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
		save();
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
	cursor = cursor->next;
	if (!cursor)
	{
		return false;
	}
	else
	{
		
		return true;
	}
}

void SCOREBOARD::ResetCursor()
{
	cursor = ScoreRecords->head;
}

void SCOREBOARD::exportScoreBoard()
{
	std::ofstream file;
	file.open("Export\\" + CourseID + ".csv");
	file << "ID,MidTerm,Final,Lab,Bonus"<< std::endl;
	if (cursor)
	{
		do
		{
			file << cursor->data->studentID << ',' << std::to_string(cursor->data->midTerm) << ',' << std::to_string(cursor->data->final) << ',' << std::to_string(cursor->data->lab) << ',' << std::to_string(cursor->data->bonus) << std::endl;
		} while (next());
	}
	file.close();
}

void SCOREBOARD::save()
{
	std::ofstream file;
	file.open("Data\\scoreboard\\" + CourseID + ".txt");
	ResetCursor();
	if (cursor)
	{
		do
		{
			file << cursor->data->studentID << ',' << std::to_string(cursor->data->midTerm) << ',' << std::to_string(cursor->data->final) << ',' << std::to_string(cursor->data->lab) << ',' << std::to_string(cursor->data->bonus) << std::endl;
		} while (next());
	}
	file.close();
}

void SCOREBOARD::Edit()
{
	ConsoleUI RecordsID(20);
	if (ScoreRecords->head)
	{
		ScoreRecords->resetCurrent();
		do
		{
			RecordsID.addLine(ScoreRecords->current->data->studentID);
		} while (ScoreRecords->next());
		RecordsID.addLine("back");
		bool isExit = false;
		while (!isExit)
		{
			RecordsID.clear();
			RecordsID.showMenu();
			RecordsID.getKey();
			if (RecordsID.getState())
			{
				if (RecordsID.getChoice() == RecordsID.exitChoice())
				{
					isExit = true;
				}
				else
				{
					ScoreRecords->resetCurrent();
					for (int i = 0; i < RecordsID.getChoice(); i++)
					{
						ScoreRecords->next();
					}
					ConsoleUI Action(10);
					Action.addLine("MidTerm");
					Action.addLine("Final");
					Action.addLine("Lab");
					Action.addLine("Bonus");
					Action.addLine("back");
					bool isBack = false;
					while (!isBack)
					{
						Action.clear();
						Action.showMenu();
						Action.getKey();
						if (Action.getState())
						{
							if (Action.getChoice() == Action.exitChoice())
							{
								isBack = true;
							}
							else
							{
								cin.ignore();
								switch (Action.getChoice())
								{
								case 0:
									cout << "Enter Midterm score: ";
									cin >> ScoreRecords->current->data->midTerm;
			
									break;

								case 1:

									cout << "Enter Final score: ";
									cin >> ScoreRecords->current->data->final;
									break;

								case 2:
									cout << "Enter Lab score: ";
									cin >> ScoreRecords->current->data->lab;
									break;

								case 3:
									cout << "Enter Bonus score: ";
									cin >> ScoreRecords->current->data->bonus;
									break;
								default:
									break;
								}
							}
						}
					}
				}
			}
		}

	}
	save();
}

bool SCOREBOARD::getResult()
{
	return result;
}


