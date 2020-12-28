#ifndef WEATHERSENS_H
#define WEATHERSENS_H

#include <string>
#include <iostream>

#include "../ConfigParser/ConfigParser.h"
#include "../DriverListParser/DriverListParser.h"
#include "../WSValueserver/WSValueserver.h"


using namespace std;

class Weathersens
{
public:
    Weathersens(ConfigParser*, ExceptionClass*);
    ~Weathersens();
    void init();
    void refreshValues();
    void stop();

    void outOverview();
    WSValueserver* getVSRef(){return vserver_;}
private:
    ConfigParser *configParser_;
    ExceptionClass *exception_;
    DriverListParser *driverListParser_;

    std::string driverListPath_;

    struct drivers driverInstances_;

    bool active_ = false;

    WSValueserver *vserver_;
};

#include "Weathersens.cpp"

#endif // WEATHERSENS_H
