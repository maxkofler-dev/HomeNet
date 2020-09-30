#include "WSValueserver.h"

WSValueserver::WSValueserver(ConfigParser* config, drivers dInstance)
{
    this->config_ = config;
    this->driversInstance_ = dInstance;
    py = new HNPython(config, dInstance);
}

WSValueserver::~WSValueserver(){
    if(active_)
    {
        cout << "Warning: WSValueserver::end() not called, please implement!" << endl;
        py->stopDrivers();
        py->finishPython();
        delete[] values_;
        active_ = false;
    }
}

void WSValueserver::init(){
    py->initPython();
    py->importDrivers();
    py->startDrivers();
    values_ = new struct value[driversInstance_.tValuesCount];
    active_ = true;
}

void WSValueserver::end(){
    py->stopDrivers();
    py->finishPython();
    delete[] values_;
    active_ = false;
}

void WSValueserver::refresh(){
    py->resumeDrivers();
    py->callValues();
    py->pauseDrivers();

    for (int i = 0; i < driversInstance_.tValuesCount; i++)
    {
        values_[i] = py->getValue(i);
    }
}

string WSValueserver::getValue(int id){
    return values_[id].value;
}

string WSValueserver::getType(int id){
    return values_[id].type;
}
