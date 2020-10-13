#ifndef WEATHERSENS_H
#define WEATHERSENS_H

#include <string>
#include <iostream>

#include "ConfigParser.h"
#include "DriverListParser.h"
#include "WSValueserver.h"


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

#endif // WEATHERSENS_H
