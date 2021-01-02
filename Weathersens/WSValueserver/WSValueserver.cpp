#include "WSValueserver.h"

WSValueserver::WSValueserver(ConfigParser* config, drivers dInstance, WSHistory* history, Log* log)
{
    this->config_ = config;
    this->driversInstance_ = dInstance;
    this->log = log;
    this->history_ = history;
    py = new HNPython(config, dInstance, this->log);
}

WSValueserver::~WSValueserver(){
    if(active_)
    {
        log->logprg("WSValueserver::~WSValueserver()", "WSValueServer::end() not called, please implement!!!", Log::W);
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

    std::string hp = config_->getConfig("historydir", true, false);

    for (int i = 0; i < driversInstance_.tValuesCount; i++)
    {
        values_[i] = py->getValue(i);
        history_->appHistory(hp + "/" + to_string(i), values_[i]);
    }
}

string WSValueserver::getValue(int id){
    return values_[id].value;
}

string WSValueserver::getType(int id){
    return values_[id].type;
}

struct valueInstance WSValueserver::getValueInstance(int id){
    struct valueInstance vI;
    vI.valueDataType = values_[id].type;
    vI.value = values_[id].value;
    vI.driverId = driversInstance_.vDriverReferences[id];
    vI.valueId = driversInstance_.vReferences[id];
    vI.driverName = driversInstance_.driverInstances[vI.driverId].dName;
    vI.valueName = driversInstance_.driverInstances[vI.driverId].vNames[vI.valueId];
    vI.valueUnit = driversInstance_.driverInstances[vI.driverId].vUnits[vI.valueId];
    vI.valueType = driversInstance_.driverInstances[vI.driverId].vTypes[vI.valueId];
    return vI;
}
