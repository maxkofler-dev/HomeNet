#ifndef WEATHERSENS_H
#define WEATHERSENS_H

#include <string>
#include <iostream>

#include "../../log/log.h"
#include "../ConfigParser/ConfigParser.h"
#include "../DriverListParser/DriverListParser.h"
#include "../WSValueserver/WSValueserver.h"
#include "../WSHistory/WSHistory.h"


using namespace std;

class Weathersens
{
public:
    Weathersens(ConfigParser*, ExceptionClass*, Log*);
    ~Weathersens();
    void init();
    void refreshValues();
    void cleanHistories();
    void stop();

    void outOverview();
    WSValueserver* getVSRef(){return vserver_;}
private:
    Log* log;
    ConfigParser *configParser_;
    ExceptionClass *exception_;
    DriverListParser *driverListParser_;
    
    std::string historyPath_;
    std::string driverListPath_;

    struct drivers driverInstances_;

    bool active_ = false;

    WSValueserver *vserver_;
    WSHistory* history_;
};

#include "Weathersens.cpp"

#endif // WEATHERSENS_H
