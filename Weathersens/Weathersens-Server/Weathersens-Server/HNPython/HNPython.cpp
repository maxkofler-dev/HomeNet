#include "HNPython.h"

HNPython::HNPython(ConfigParser* cfg, struct drivers dInst)
{
    config_ = cfg;
    driversInstance_ = dInst;
}

void HNPython::initPython(){
    Py_Initialize();
    PyRun_SimpleString("import sys");
    driverPath_ = config_->getConfig("driverpath", true, false);
    workDir_ = config_->getConfig("workdir", true, false);
    string exec = "sys.path.append(\"" + driverPath_ + "\")";
    PyRun_SimpleString(exec.c_str());
}
void HNPython::finishPython(){
    Py_Finalize();
}


void HNPython::importDrivers(){
    int driverCount = driversInstance_.driverCount;
    valuesBuffer_ = new struct value[driversInstance_.tValuesCount];
    string command;
    for (int i = 0; i < driverCount; i++)
    {
        command = "import " + driversInstance_.driverInstances[i].dName + ".main as driver" + to_string(i);
        PyRun_SimpleString(command.c_str());
        cout << "Imported a driver with command: " << command << endl;
    }
}

void HNPython::startDrivers(){
    string command;
    for (int i = 0; i < driversInstance_.driverCount; i++){
        command = "driver" + to_string(i) + ".start(" + to_string(i) + ", \"" + driverPath_ + "\")";
        PyRun_SimpleString(command.c_str());
    }
}

void HNPython::resumeDrivers(){
    string command;
    for (int i = 0; i < driversInstance_.driverCount; i++){
        command = "driver" + to_string(i) + ".resume()";
        PyRun_SimpleString(command.c_str());
    }
}

void HNPython::pauseDrivers(){
    string command;
    for (int i = 0; i < driversInstance_.driverCount; i++){
        command = "driver" + to_string(i) + ".pause()";
        PyRun_SimpleString(command.c_str());
    }
}

void HNPython::stopDrivers(){
    string command;
    for (int i = 0; i < driversInstance_.driverCount; i++){
        command = "driver" + to_string(i) + ".stop()";
        PyRun_SimpleString(command.c_str());
    }
}

void HNPython::callValues(){
    int gID = 0;
    for (int n = 0; n < driversInstance_.driverCount; n++){
        for (int i = 0; i < driversInstance_.driverInstances[n].valueCount; i++){
            string command;

            command = "driver" + to_string(n) + ".getValue(" + to_string(gID);
            command += ", " + to_string(i);
            command += ", \"" + workDir_ + "\")";
            PyRun_SimpleString(command.c_str());
            valuesBuffer_[gID] = getValueReturn(workDir_, gID);
            gID++;
        }
    }
}

struct value HNPython::getValueReturn(string wp, int ID){
    struct value vReturn;
    ifstream file;
    string buffer;
    string path = (wp + "/valueReturn/" + to_string(ID));
    file.open(path.c_str(), ios::in);
    getline(file, buffer);
    int pos [4] = {0};
    pos[0] = buffer.find("<");
    pos[1] = buffer.find(">", pos[0]);
    pos[2] = buffer.find("<", pos[1]);
    pos[3] = buffer.find(">", pos[2]);

    string type;
    for (int i = pos[0] + 1; i < pos[1]; i++){
        type += buffer[i];
    }

    string value;
    for (int i = pos[2] + 1; i < pos[3]; i++){
        value += buffer[i];
    }

    time_t now = time(0);

    fstream history;
    history.open(wp + "/valueHistory/" + to_string(ID), ios::app);
    history << now << ";" << value << endl;
    history.close();

    vReturn.type = type;
    vReturn.value = value;

    file.close();

    return vReturn;
}
