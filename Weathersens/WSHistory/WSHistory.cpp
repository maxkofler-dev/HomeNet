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

void WSHistory::appHistory(std::string path, struct value v){
    struct History::history_entry history_entry;
    history_entry.type = v.type;
    history_entry.value = v.value;
    time_t now = time(0);
    history_entry.time = now;

    this->history->loadFile(path);
    this->history->appHistory(history_entry);
}

std::string WSHistory::getHistory(std::string path){
    using namespace std;
    this->history->loadFile(path);
    this->history->loadHistory();
    return this->history->getHistory();
}

std::string WSHistory::getHistory(std::string path, int lookback){
    using namespace std;
    this->history->loadFile(path);
    this->history->loadHistory();
    return this->history->getHistory(lookback);
}