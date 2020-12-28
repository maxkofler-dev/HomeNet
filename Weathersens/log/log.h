#ifndef __LOG_H__
#define __LOG_H__

#include <string>
#include <iostream>

enum LOG{
    V = 1,
    E = 2,
    W = 3,
    D = 4,
};

class Log{

public:
    Log(){}
    Log(int curLevel){
        setLevel(curLevel);
    }

    void setLevel(int level){
        lLevel = level;
    }

    const static int V = 1;
    const static int I = 2;
    const static int W = 3;
    const static int E = 4;
    const static int D = 5;


    //Default logging
    void log(std::string tag, std::string msg, int loglevel){
        std::cout << "[" << loglevel << "]" << tag << " - " << msg << std::endl;
    }
    void log(std::string tag, std::string msg){
        std::cout << "[---]" << tag << " - " << msg << std::endl; 
    }
    void log(std::string msg){
        std::cout << "[---]" << msg << std::endl;
    }
    

    //Logging for program errors, like warnings for programmers
    void logprg(std::string function, std::string msg, int loglevel){
        std::cout << "(" << loglevel << ")" << "{prg-log}" << "[" << function << "]" << msg << std::endl;
    }



private:
    int lLevel;
};

#endif