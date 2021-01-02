#ifndef __WSHISTORY_H__
#define __WSHISTORY_H__

#include <string>
#include <ctime>

#include "../../log/log.h"
#include "history/history.h"
#include "../WSValueserver/WSValueserver.h"

class WSHistory{
public: 
    WSHistory(Log*);

    void cleanHistories(std::string, int, std::string);
    void appHistory(struct value);

    std::string getHistory(std::string);
    std::string getHistory(std::string, int);

private:
    Log* log;

    History* history;
};

#include "WSHistory.cpp"

#endif