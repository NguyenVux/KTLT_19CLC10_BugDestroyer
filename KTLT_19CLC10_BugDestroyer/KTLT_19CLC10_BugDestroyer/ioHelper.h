#ifndef  _IOHELPER_H
#define _IOHELPER_H
#include <string>
#include <Windows.h>
class ioHelper
{
public:
	static std::string centered(std::string text, int cellSize);
	static void whiteLine();
	static void blackLine();
};
#endif



