#include "WSHistory.h"

WSHistory::WSHistory(Log* log){
    this->log = log;
    this->history = new History(log);
}

void WSHistory::cleanHistories(std::string prefix, int cHistories, std::string postfix){
    using namespace std;
    string pathToHistory;
    for (int i = 0; i < cHistories; i++){
        pathToHistory = prefix + to_string(i) + postfix;
        this->history->loadFile(pathToHistory);
        this->history->cleanHistory();
        this->history->closeFile();
    }
}