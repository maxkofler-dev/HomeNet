#include "Weathersens.h"

Weathersens::Weathersens(ConfigParser* cp, ExceptionClass* exc){
    this->configParser_ = cp;
    this->exception_ = exc;
}

Weathersens::~Weathersens(){
    if (active_)
    {
        stop();
    }
}

//Method to initialize the Weathersens-Module
void Weathersens::init(){
    //Only continue if the Configuration was parsed
    if (!configParser_->configParsed())
    {
        exception_->setECC("WS-IN-1");
        throw exception_;
    }

    //Parse the critical configurations...
    driverListPath_ = configParser_->getConfig("driverListPath", true, false);

    //Parse the driver list and get the driver information
    driverListParser_ = new DriverListParser(driverListPath_, exception_);
    driverListParser_->parseList();

    driverInstances_ = driverListParser_->getInstances();

    for (int i = 0; i < driverInstances_.driverCount; i++)
    {
        driverListParser_->coutDriver(driverInstances_.driverInstances[i]);
    }

    vserver_ = new WSValueserver(configParser_, driverInstances_);

    vserver_->init();
    active_ = true;
}

void Weathersens::refreshValues(){
    vserver_->refresh();
}

void Weathersens::stop(){
    vserver_->end();
    delete vserver_;
    active_ = false;
}

void Weathersens::outOverview(){
    string o;
    o += "-----Value overview-----\n";
    for (int i = 0; i < driverInstances_.tValuesCount; i++)
    {
        o += driverInstances_.driverInstances[driverInstances_.vDriverReferences[i]].vNames[driverInstances_.vReferences[i]];
        o += "(driver" + to_string(driverInstances_.vDriverReferences[i]) + ") = " + vserver_->getValue(i) + "\n";
    }
    o += "-\n";
    cout << o << endl;
}
