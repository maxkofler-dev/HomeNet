#ifndef WSVALUESERVER_H
#define WSVALUESERVER_H

#include <string>
#include <iostream>

#include "ConfigParser.h"
#include "DriverListParser.h"
#include "HNPython.h"

using namespace std;

class WSValueserver
{
public:
    WSValueserver(ConfigParser*, drivers);
    ~WSValueserver();

    void init();
    void refresh();
    void end();

    string getValue(int);
    string getType(int);

private:
    bool active_= false;
    ConfigParser* config_;
    drivers driversInstance_;

    HNPython *py;
    struct value *values_;
};

#endif // WSVALUESERVER_H
