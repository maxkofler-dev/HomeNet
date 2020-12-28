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
#include <iostream>

#include "WSValueserver.h"
#include "ConfigParser.h"

class HNNetworking
{
public:
    HNNetworking(WSValueserver*, ConfigParser*);
    void runNetwork();
    void sendVSPack(int, std::string);
    string packValue(int);

private:
    WSValueserver* vSRef_;
    ConfigParser* cp_;

};

#endif // HNNETWORKING_H
