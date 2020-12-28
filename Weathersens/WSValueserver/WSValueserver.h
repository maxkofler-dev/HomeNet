#ifndef WSVALUESERVER_H
#define WSVALUESERVER_H

#include <string>

#include "../../log/log.h"
#include "../ConfigParser/ConfigParser.h"
#include "../DriverListParser/DriverListParser.h"
#include "../HNPython/HNPython.h"

using namespace std;

struct valueInstance{
    std::string driverName;
    int driverId;
    std::string valueName;
    std::string valueUnit;
    std::string valueType;
    int valueId;


    std::string value;
    std::string valueDataType;
};

class WSValueserver
{
public:
    WSValueserver(ConfigParser*, drivers, Log*);
    ~WSValueserver();

    void init();
    void refresh();
    void end();

    string getValue(int);
    string getType(int);

    int getValueCount(){return driversInstance_.tValuesCount;}

    struct valueInstance getValueInstance(int);

private:
    Log* log;
    bool active_= false;
    ConfigParser* config_;
    drivers driversInstance_;

    HNPython *py;
    struct value *values_;
};

#include "WSValueserver.cpp"

#endif // WSVALUESERVER_H
