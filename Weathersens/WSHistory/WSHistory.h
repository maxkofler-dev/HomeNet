#ifndef __WSHISTORY_H__
#define __WSHISTORY_H__

#include <string>

#include "../../log/log.h"
#include "history/history.h"

class WSHistory{
public: 
    WSHistory(Log*);

    void cleanHistories(std::string, int, std::string);
private:
    Log* log;

    History* history;
};

#include "WSHistory.cpp"

#endif