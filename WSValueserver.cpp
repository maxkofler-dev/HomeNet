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
