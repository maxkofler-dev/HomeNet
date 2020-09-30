#ifndef WSPYTHON_H
#define WSPYTHON_H

#include <Python.h>
#include <string>
#include <iostream>
#include <fstream>

#include "ConfigParser.h"
#include "DriverListParser.h"

using namespace std;

struct value{
    string type;
    string value;
};

class HNPython
{
public:
    HNPython(ConfigParser*, struct drivers);

    void initPython();
    void finishPython();

    void importDrivers();
    void callValues();

    void startDrivers();
    void resumeDrivers();
    void pauseDrivers();
    void stopDrivers();

    struct value getValue(int i){return valuesBuffer_[i];}

    void execTrigger(int);
private:
    struct value getValueReturn(string, int);

    ConfigParser* config_;
    struct drivers driversInstance_;

    string workDir_;
    string driverPath_;

    struct value *valuesBuffer_;
};

#endif // WSPYTHON_H
