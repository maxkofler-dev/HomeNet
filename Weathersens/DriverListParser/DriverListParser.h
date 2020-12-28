#pragma once
#ifndef DRIVERLISTPARSER
#define DRIVERLISTPARSER

#include <string>
#include <fstream>
#include <iostream>
#include <vector>

#include "../StartupMsg/StartupMsg.h"
#include "../ExceptionClass/ExceptionClass.h"
using namespace std;

struct driver
{
    bool driverFound;

    string dName;
    int valueCount;
    int triggerCount;

    int *vIDs;
    int *gvIDs;
    string *vNames;
    string *vUnits;
    string *vTypes;

    int *tIDs;
    int *gtIDs;
    string *tNames;
    string *tFunctions;
    string *tTypes;
};

struct drivers
{
    int driverCount;
    int tValuesCount;
    int tTriggerCount;
    int *vDriverReferences;
    int *vReferences;
    struct driver *driverInstances;
};

class DriverListParser
{
public:
    DriverListParser(string, ExceptionClass*);

	void parseList();
    void coutDriver(struct driver);
    struct drivers getInstances(){return driverInstances;}

private:
    ifstream cFile;

    struct driver loadDriver();
    bool parseDriverMember(string, struct driver*);

	int countDrivers(string);
    ExceptionClass* exClass;
	string path;
	int cDrivers;
    int cValidDrivers;

    string *buffer;

    int tIndex;
    int vIndex;

    int gvIndex;
    int gtIndex;

    struct drivers driverInstances;
};

#include "DriverListParser.cpp"

#endif
