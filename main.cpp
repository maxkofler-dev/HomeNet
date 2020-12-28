
#include <iostream>
#include <unistd.h>
#include <thread>

#include "log/log.h"
#include "Weathersens/ConfigParser/ConfigParser.h"
#include "Weathersens/ExceptionClass/ExceptionClass.h"
#include "Weathersens/Weathersens/Weathersens.h"
#include "Weathersens/HNNetworking/HNNetworking.h"

void runNet(HNNetworking* hnw, Log* log){
    hnw->runNetwork();
    log->log("runNet()", "Network ended!", Log::I);
}

int main(int argc, char** argv)
{
    ExceptionClass ec;
    ec.setup("errors");

    try{
        Log log(6);
        ConfigParser cp(&ec, &log);
        cp.parseConfig("/hn/config.txt");
        int timeSleep = stoi(cp.getConfig("timesleep", true, false));
        Weathersens ws(&cp, &ec, &log);
        ws.init();
        HNNetworking hnw(ws.getVSRef(), &cp, &log);
        std::thread netThread(runNet, &hnw, &log);
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
