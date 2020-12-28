#ifndef HNNETWORKING_H
#define HNNETWORKING_H

#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#include <fstream>
#include <string>

#include "../../log/log.h"
#include "../WSValueserver/WSValueserver.h"
#include "../ConfigParser/ConfigParser.h"

class HNNetworking
{
public:
    HNNetworking(WSValueserver*, ConfigParser*, Log*);
    void runNetwork();
    void sendVSPack(int, std::string);
    string packValue(int);

private:
    Log* log;
    WSValueserver* vSRef_;
    ConfigParser* cp_;

};

#include "HNNetworking.cpp"

#endif // HNNETWORKING_H
