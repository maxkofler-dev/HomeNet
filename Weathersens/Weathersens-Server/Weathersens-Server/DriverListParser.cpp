#include "DriverListParser.h"

DriverListParser::DriverListParser(string path, ExceptionClass* exc)
{
	this->path = path;
    this->exClass = exc;
}

void DriverListParser::parseList()
{
    cFile.open(path, ios::in);
    if (cFile.fail())
    {
        exClass->setECC("HN-LD-1");
        throw exClass;
    }
    struct driver newDI;
    vector<struct driver> driverInstancesVector;
    int driverCount = 0;

    gtIndex = 0;
    gvIndex = 0;

    while (!cFile.eof())
    {
        newDI = loadDriver();
        if (newDI.driverFound)
        {
            driverInstancesVector.push_back(newDI);
            driverCount++;
        }
        else
        {
            break;
        }
    }

    driverInstances.driverCount = driverCount;
    driverInstances.tValuesCount = gvIndex;
    driverInstances.tTriggerCount = gtIndex;
    driverInstances.vDriverReferences = new int [gvIndex];
    driverInstances.vReferences = new int[gvIndex];
    driverInstances.driverInstances = new struct driver[driverCount];

    int indexV = 0;

    for (int i = 0; i < driverCount; i++)
    {
        driverInstances.driverInstances[i] = driverInstancesVector.at(i);
        for(int n = 0; n < driverInstancesVector.at(i).valueCount; n++){
            driverInstances.vDriverReferences[indexV] = i;
            driverInstances.vReferences[indexV] = n;
            indexV++;
        }
    }
}

struct driver DriverListParser::loadDriver(){
    struct driver driverInstance;
    driverInstance.driverFound = false;
    //If the file is not accesable anymore
    if (cFile.fail())
    {
        exClass->setECC("HN-LD-2");
        throw exClass;
    }

    unsigned int openSigns[4] = {0};
    unsigned int closeSigns[4] = {0};
    int lastPos;

    buffer = new string;
    getline (cFile, *buffer);
    if (cFile.eof())
    {
        return driverInstance;
    }
    cout << "New line: " << *buffer << endl;

    bool openSignOutOfIndex = false;
    bool closeSignOutOfIndex = false;

    //Search the start and stop signs for the arguments

    for (int i = 0; i < 4; i++)
    {
        //Find the start sign of i argument and check if it is valid
        if (i == 0){
            openSigns[i] = buffer->find('<');
        }else{
            openSigns[i] = buffer->find('<', lastPos);
        }
        if (openSigns[i] > buffer->length()){
           openSignOutOfIndex = true;
           break;
        }
        lastPos = openSigns[i];

        //Find the end sign of i argument and check if it is valid
        closeSigns[i] = buffer->find('>', lastPos);
        if (closeSigns[i] > buffer->length()){
            closeSignOutOfIndex = true;
            break;
        }
        lastPos = closeSigns[i];
    }

    //If any sign is out of index, throw an error!
    if (openSignOutOfIndex || closeSignOutOfIndex)
    {
        exClass->setECC("HN-LD-3");
        throw exClass;
    }

    string args[4] = {""};

    //Store the arguments into an array
    for (unsigned int n = 0; n < 4; n++)
    {
        for (unsigned int i = openSigns[n] + 1; i < closeSigns[n]; i++)
        {
            args[n] = args[n] + buffer->at(i);
        }
        cout << "arg" << n << ": " << args[n] << endl;
    }

    if (args[0] == "driver")
    {
        driverInstance.driverFound = true;
        driverInstance.dName = args[1];
        driverInstance.valueCount = stoi(args[2]);
        driverInstance.triggerCount = stoi(args[3]);

        //Reserve memory for the new arguments of the values
        driverInstance.vIDs = new int[driverInstance.valueCount];
        driverInstance.gvIDs = new int[driverInstance.valueCount];
        driverInstance.vNames = new string[driverInstance.valueCount];
        driverInstance.vUnits = new string[driverInstance.valueCount];
        driverInstance.vTypes = new string[driverInstance.valueCount];

        //Reserve memory for the new arguments of the triggers
        driverInstance.tIDs = new int[driverInstance.triggerCount];
        driverInstance.gtIDs = new int[driverInstance.triggerCount];
        driverInstance.tNames = new string[driverInstance.triggerCount];
        driverInstance.tFunctions = new string[driverInstance.triggerCount];
        driverInstance.tTypes = new string[driverInstance.triggerCount];

        bool driverEnd = false;
        bool memberFound = false;

        vIndex = 0;
        tIndex = 0;

        string nBuffer;

        while (!driverEnd){
            getline(cFile, nBuffer);
            cout << "New memberline: " << nBuffer << endl;
            memberFound = parseDriverMember(nBuffer, &driverInstance);
            driverEnd = !memberFound;
        }
    }

    return driverInstance;
}

bool DriverListParser::parseDriverMember(string buffer, struct driver* driverInstance){
    bool memberFound = false;

    unsigned int openSigns[5] = {0};
    unsigned int closeSigns[5] = {0};
    int lastPos = 0;

    bool openSignOutOfIndex = false;
    bool closeSignOutOfIndex = false;

    for (int i = 0; i < 5; i++)
    {
        //Find the start sign of i argument and check if it is valid
        openSigns[i] = buffer.find("<", lastPos);
        if (openSigns[i] > buffer.length()){
           openSignOutOfIndex = true;
           break;
        }
        lastPos = openSigns[i];
        //Find the end sign of i argument and check if it is valid
        closeSigns[i] = buffer.find(">", lastPos);
        if (closeSigns[i] > buffer.length()){
            closeSignOutOfIndex = true;
            break;
        }
        lastPos = closeSigns[i];
    }

    //If any sign is out of index, throw an error!
    if (openSignOutOfIndex || closeSignOutOfIndex)
    {
        return memberFound;
    }

    string args[5] = {""};
    //Store the arguments into an array
    for (unsigned int n = 0; n < 5; n++)
    {
        for (unsigned int i = openSigns[n] + 1; i < closeSigns[n]; i++)
        {
            args[n] += buffer[i];
        }
    }

    if (!args[0].compare("value")){
        //If the member is a value, store its information
        cout << "value" << endl;
        driverInstance->vIDs[vIndex] = stoi(args[1]);
        driverInstance->gvIDs[vIndex] = gvIndex;
        driverInstance->vTypes[vIndex] = args[2];
        driverInstance->vNames[vIndex] = args[3];
        driverInstance->vUnits[vIndex] = args[4];
        gvIndex++;
        vIndex++;
        memberFound = true;
    }else if (!args[0].compare("trigger")){
        //Same for triggers
        cout << "trigger" << endl;
        driverInstance->tIDs[tIndex] = stoi(args[1]);
        driverInstance->gtIDs[tIndex] = gtIndex;
        driverInstance->tTypes[tIndex] = args[2];
        driverInstance->tNames[tIndex] = args[3];
        driverInstance->tFunctions[tIndex] = args[4];
        gtIndex++;
        tIndex++;
        memberFound = true;
    }else if (args[0].compare("/value")){
        cout << "End of driver block!" << endl;
    }else{
        cout << "unknown" << endl;
    }

    return memberFound;
}

void DriverListParser::coutDriver(struct driver instance){
    string out = "";
    out += "Drivername " + instance.dName + "\n";
    out += "Valuecount: " + to_string(instance.valueCount);
    out += " Triggercount: " + to_string(instance.triggerCount) + "\n\n";

    for (int i = 0; i < instance.valueCount; i++)
    {
        out += "ValueID: " + to_string(instance.vIDs[i]) + "\n";
        out += "Global ID: " + to_string(instance.gvIDs[i]) + "\n";
        out += "Valuename: " + instance.vNames[i] + "\n";
        out += "ValueUnit: " + instance.vUnits[i] + "\n";
        out += "Valuetype: " + instance.vTypes[i] + "\n-\n";
    }

    for (int i = 0; i < instance.triggerCount; i++)
    {
        out += "TriggerID: " + to_string(instance.tIDs[i]) + "\n";
        out += "Global ID: " + to_string(instance.gtIDs[i]) + "\n";
        out += "Triggerame: " + instance.tNames[i] + "\n";
        out += "Triggerfunction: " + instance.tFunctions[i] + "\n";
        out += "Triggertype: " + instance.tTypes[i] + "\n-\n";
    }

    cout << out;

}
