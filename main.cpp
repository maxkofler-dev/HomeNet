
#include <iostream>
#include <unistd.h>
#include <thread>

#include "Weathersens/ConfigParser/ConfigParser.h"
#include "Weathersens/ExceptionClass/ExceptionClass.h"
#include "Weathersens/Weathersens/Weathersens.h"
#include "Weathersens/HNNetworking/HNNetworking.h"

void runNet(HNNetworking* hnw){
    hnw->runNetwork();
    std::cout << "Networking ended!" << std::endl;
}

int main(int argc, char** argv)
{
    ExceptionClass ec;
    ec.setup("errors");

    try{
        ConfigParser cp(&ec);
        cp.parseConfig("/hn/config.txt");
        int timeSleep = stoi(cp.getConfig("timesleep", true, false));
        Weathersens ws(&cp, &ec);
        ws.init();
        HNNetworking hnw(ws.getVSRef(), &cp);
        std::thread netThread(runNet, &hnw);
        while (true)
        {
            ws.refreshValues();
            ws.outOverview();
            usleep(1000000 * timeSleep);
        }
        netThread.join();
    }catch(ExceptionClass* e)
    {
        e->printExceptionText();
    }
}
