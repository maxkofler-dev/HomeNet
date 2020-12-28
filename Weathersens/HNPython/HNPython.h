#ifndef WSPYTHON_H
#define WSPYTHON_H

#include <Python.h>
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>

#include "../ConfigParser/ConfigParser.h"
#include "../DriverListParser/DriverListParser.h"

struct value{
    std::string type;
    std::string value;
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
    struct value getValueReturn(int);

    ConfigParser* config_;
    struct drivers driversInstance_;

    std::string workDir_;
    std::string historyDir_;
    std::string driverPath_;

    struct value *valuesBuffer_;
};

#include "HNPython.cpp"

#endif // WSPYTHON_H
