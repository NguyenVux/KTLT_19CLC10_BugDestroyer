#include "ioHelper.h"

std::string ioHelper::centered(std::string text, int cellSize)
{
	std::string result;
	if (cellSize <= text.length()-1)
	{
		return text.substr(0, cellSize);
	}
	result = std::string(cellSize / 2 - text.length() / 2, ' ') + text;
	return result;
}

void ioHelper::whiteLine()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
}

void ioHelper::blackLine()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void ioHelper::textYellow()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
}

void ioHelper::textGreen()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10 );
}

void ioHelper::textRed()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
}
