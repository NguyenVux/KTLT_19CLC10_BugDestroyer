#include "typeConverter.h"

int converter::strToInt(std::string input)
{
	int result = 0;
	int power = 1;
	for (int i = input.length() - 1; i >= 0; i--)
	{
		result += (input[i] - 48) * power;
		power *= 10;
	}
	return result;
}

int converter::charToInt(char input)
{
	return input - 48;
}