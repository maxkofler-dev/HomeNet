
/*

functions with "n<-" instead of "<-" return null on failure!
functions with "s/f" as return indicate that a boolean tells of success or failure!


-loadFile(string filepath)
    ->  the name of the history file to load into the class
    !!  Stores the string in the curFile member variable to process it
    <-  s/f

-openFile()
    ->  /
    !!  Opens the file specified in loadFile() to process
    <-  s/f

-getHistory();
    ->  /
    !!  Reads the file specified in loadFile()
    n<- The whole history packed as a string

-getHistory(time_t lookbackWindow)
    ->  The time in seconds to look back
    !!  Uses getHistory() to load the history, shortens it to the specified time window
    n<- The window including the values specified

-loadHistory()
    ->  /
    !!  Loads the history specified into the cache
    <-  The ammount of entries loaded

-cleanHistory()
    ->  /
    !!  Loads the history and rewrites it excluding corrupt entries
    <-  The ammount of rewritten values
*/



#ifndef __HISTORY_H__
#define __HISTORY_H__

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "../log/log.h"

class History{

public:
    History(Log* log);
    ~History();

    bool loadFile(std::string file_path);
    bool openFile();
    void closeFile();

    void clearCache();


    std::string getHistory();
    std::string getHistory(time_t backsight);

    int loadHistory();
    int cleanHistory();

    struct history_entry{
        int time;
        std::string type;
        std::string value;
    };

private:
    Log* log;

    std::ifstream history_file;
    std::string curFile;

    bool fileLoaded;
    bool historyLoaded;

    struct history_entry* history_entries;
    int entryCount;
};

#include "history.cpp"

#endif