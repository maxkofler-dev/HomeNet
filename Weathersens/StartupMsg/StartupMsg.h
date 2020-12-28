#pragma once
#ifndef STARTUPWARNINGS
#define STARTUPWARNINGS

#include <string>
#include <iostream>
#include <fstream>

using namespace std;


class StartupMsg
{
public:
	StartupMsg(string);
	void putWarning(int, string);
	void clear();
private:
	fstream warningsList;
	string path = "startupWarnings.wswarnings";
};

#include "StartupMsg.cpp"

#endif // !STARTUPWARNINGS
