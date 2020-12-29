#include "history.h"

History::History(Log* log){
    this->log = log;
}

History::~History(){
    if (this-historyLoaded){
        closeFile();
        clearCache();
    }
}


bool History::loadFile(std::string filename){
    if (!filename.empty()){
        //Save the file path
        this->curFile = filename;
        this->fileLoaded = true;
        log->log("History::laodFile()", "Loaded file \"" + this->curFile + "\"", Log::D);

        return true;
        
    }else{
        log->log("History::loadFile()", "Filename is empty!", Log::E);
        return false;while(1){
        
    }
    }
}

bool History::openFile(){
    if (this->fileLoaded){
        //Close the file before opening it
        if (this->history_file.is_open()){
            history_file.close();
            log->logprg("History::openFile()", "File was already opened! Please make shure to close the file properly!", Log::W);
        }

        //Then open it
        this->history_file.open(this->curFile, std::ios::in);

        if (this->history_file.is_open()){
            return true;
        }else{
            log->log("History::openFile()", "File could not be opened!", Log::E);
            return false;
        }

        return this->history_file.good();
        
    }else{
        this->fileLoaded = false;
        log->logprg("History::openFile()", "No filepath speciefied to open!", Log::E);
        return false;
    }
}

void History::closeFile(){
    if (this->history_file.is_open()){
        history_file.close();
    }else{
        log->logprg("History::closeFile()", "The file was not opened - nothig to close!", Log::W);
    }
}

void History::clearCache(){
    if (historyLoaded){
        this->historyLoaded = false;
        this->entryCount = 0;
        delete[] this->history_entries;
    }
}

std::string History::getHistory(){
    if (historyLoaded){
        
    }else{
        log->logprg("History::getHistory()", "History was not loaded yet, loading it now, please make shure to load your history before reading it!", Log::W);
        loadHistory();
    }

    std::string buf;
    for (int i = 0; i < this->entryCount; i++){
        buf += std::to_string(this->history_entries[i].time) + ";";
        buf += this->history_entries[i].type + ";";
        buf += this->history_entries[i].value + "\n";
    }
    return buf;
}

std::string History::getHistory(time_t lookback){
    if (!historyLoaded){
        log->logprg("History::getHistory(time_t lookback)", "History was not loaded yet, loading it now, please make shure to load your history before reading it!", Log::W);
        loadHistory();
    }

    int firstUNIXTime = this->history_entries[0].time;
    int lastUNIXTime = this->history_entries[this->entryCount-1].time;

    //Check if there is even work to do
    if (lastUNIXTime - lookback < firstUNIXTime){
        log->log("History::getHistory(time_t lookback)", "There is no work to do for cutting the values to the right window!", Log::I);
        return getHistory();
    }

    int startTime = lastUNIXTime - lookback;
    int curEntry = 0;
    int time;

    while(curEntry < this->entryCount){
        time = this->history_entries[curEntry].time;
        if (time > startTime){
            break;
        }
        curEntry++;
    }

    curEntry--;

    log->log("History::getHistory(time_t lookback)", "Requested time=" + std::to_string(startTime) + " found time=" + std::to_string(history_entries[curEntry].time), Log::D);

    std::string buf = "";
    for (int i = curEntry; i < this->entryCount-1; i++){
        buf += std::to_string(this->history_entries[i].time) + ";";
        buf += this->history_entries[i].type + ";";
        buf += this->history_entries[i].value + "\n";
    }


    return buf;
}

int History::loadHistory(){
    using namespace std;
    this->historyLoaded = false;
    string curLine;

    string timeString;
    string type;
    string value;
    int time;

    int timeEndPos;
    int typeEndPos;

    vector<history_entry> entryV;
    this->entryCount = 0;

    if (this->history_file.is_open()){
        log->log("History::getHistory()", "Reading history...", Log::D);


        while(!this->history_file.eof()){
            curLine = "";
            getline(this->history_file, curLine);
            //log->log("string", "Loaded string: " + curLine, Log::D);
            if (curLine.empty()){
                break;
            }
            
            
            timeEndPos = curLine.find(';');
            typeEndPos = curLine.find(';', timeEndPos+1);
            
            timeString = "";
            type = "";
            value = "";

            if (timeEndPos <= (int)curLine.length() && typeEndPos <= (int)curLine.length()){
                
                for(int i = 0; i < timeEndPos; i++){
                    timeString += curLine[i];
                }

                for (int i = timeEndPos+1; i < typeEndPos; i++){
                    type += curLine[i];
                }

                for (int i = typeEndPos+1; i < (int)curLine.length(); i++){
                    value += curLine[i];
                }

                try{
                    time = stoi(timeString);
                    entryV.push_back(history_entry{time, type, value});
                    this->entryCount++;
                }catch(std::out_of_range const& e){
                    log->log("History::loadHistory()", "(out_of_range)Error in getting time from string: " + timeString, Log::E);
                }catch(std::invalid_argument const& e){
                    log->log("History::loadHistory()", "(invalid_argument)Error in getting time from string: " + timeString, Log::E);
                }
                

            }else{
                log->log("History::loadHistory()", "Could not find an entry in the following etry: \"" + curLine + "\"!", Log::E);
            }

            this->historyLoaded = true;

        }
    }else{
        log->logprg("History::getHistory()", "The history file is not opened!", Log::E);
    }

    log->log("History::loadHistory()", "Loaded " + to_string(this->entryCount) + " entries!", Log::D);

    this->history_entries = new history_entry[this->entryCount];

    for (int i = 0; i < this->entryCount; i++){
        history_entries[i] = entryV.at(i);
    }

    return this->entryCount;
}


//Reads the history and then overwrites the old file, excluding unreadable entries
int History::cleanHistory(){
    using namespace std;
    loadHistory();
    if (this->historyLoaded){
        closeFile();
        fstream outFile;
        outFile.open(this->curFile, ios::out);
        for (int i = 0; i < this->entryCount; i++){
            outFile << history_entries[i].time << ";";
            outFile << history_entries[i].type << ";";
            outFile << history_entries[i].value << endl;;
        }
        outFile.close();
        log->log("History::cleanHistory()", "Rewritten " + to_string(this->entryCount) + " entries!", Log::D);
        clearCache();
        openFile();
        loadHistory();
        return this->entryCount;
    }else{
        log->log("History::cleanHistory()", "Failed opening the history file!", Log::E);
        return -1;
    }
}