#pragma once

#ifndef CONFIGPARSER
#define CONFIGPARSER

#include <string>
#include <fstream>
#include "../ExceptionClass/ExceptionClass.h"
#include "../../log/log.h"

using namespace std;

class ConfigNotFoundException
{
public:
	ConfigNotFoundException(string configName)
	{
		this->configName = configName;
	}
	string configName;
};

class CriticalConfigNotFoundException
{
public:
	CriticalConfigNotFoundException(string configName)
	{
		this->configName = configName;
	}
	string configName;
};

class ConfigParser
{
public:
    ConfigParser(ExceptionClass*, Log*);
	void parseConfig(string);
	string getConfig(string, bool, bool);

    bool configParsed(){return configParsed_;}
private:
	Log* log;
	string* configNames;
	string* configs;

	int configsCount;

    bool configParsed_;

    ExceptionClass *exception;
};

#include "ConfigParser.cpp"

#endif // !CONFIGPARSER
