#include "HNNetworking.h"

HNNetworking::HNNetworking(WSValueserver* ref, ConfigParser* cp, Log* log)
{
    this->vSRef_ = ref;
    this->cp_ = cp;
    this->log = log;
    this->history_ = new WSHistory(this->log);
}

void HNNetworking::runNetwork(){
    using namespace std;
    log->log("HNNetworking::runNetwork()", "Starting network!", Log::I);
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int port = 8090;
    if (sock < 0)
    {
        log->log("HNNetworking::runNetwork()", "Error in creating socket!", Log::E);
        return;
    }
    struct sockaddr_in server;
    int y = 1;
    setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));    //Make the Port reusable without waiting for 2 minutes

    memset(&server, 0, sizeof(server));
    //IP-Adress
    server.sin_family = AF_INET;
    //Every IP is ok
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    //Port 8080
    server.sin_port = htons(port);

    if (bind(sock, (struct sockaddr*) & server, sizeof(server)) < 0)
    {
        log->log("HNNetworking::runNetwork()", "Error in binding server!", Log::E);
        return;
    }

    if (listen(sock, 5) == -1)
    {
        log->log("HNNetworking::runNetwork()", "Error in listening on socket!", Log::E);
        return;
    }

    struct sockaddr_in client;
    int sock2;
    socklen_t len;
    char buffer[1024] = { 0 };

    while (true){
        //bool isConnected = false;
        len = sizeof(client);
        sock2 = accept(sock, (struct sockaddr*) & client, &len);
        if (sock2 < 0)
        {
            log->log("HNNetworking::runNetwork()", "Error in connecting to client!", Log::E);
        }
        else
        {
            //isConnected = true;
            std::string msg;
            int lenmsg = recv(sock2, buffer, 1024, 0);
            
            for (int i = 0; i < lenmsg; i++)
            {
                msg += buffer[i];
            }
            log->log("HNNetworking::runNetwork()", "Message incoming: " + msg, Log::I);
            sendVSPack(sock2, msg);
            //isConnected = false;
            close(sock2);
        }
    }
}

void HNNetworking::sendVSPack(int sockClient, std::string msg){
    cout << msg << endl;
    if(msg.find("@va") <= msg.length()){
        log->log("HNNetworking::runNetwork()", "Synching current live data with device!", Log::I);
        std::string buf;
        for (int i = 0; i < vSRef_->getValueCount(); i++){
            buf += this->packValue(i) + "\n";
        }
        send(sockClient, buf.c_str(), buf.length(), 0);
    }else if (msg.find("@vh") <= msg.length()){
        string buf;
        for (int i = msg.find("@vh") + 3; i < (int)msg.length(); i++){
            buf += msg[i];
        }
        int id = stoi(buf);
        log->log("HNNetworking::runNetwork()", "Called history of value " + to_string(id), Log::I);
        string hp = cp_->getConfig("historydir", true, false);

        /*
        ifstream histFile;
        histFile.open(wp + "/valueHistory/" + to_string(id), ios::in);
        string out;
        while(histFile.good() && !histFile.eof()){
            getline(histFile, buf);
            out += buf + "\n";
        }
        histFile.close();
        */

        std::string out;
        out = this->history_->getHistory(hp + "/" + to_string(id));
        

        send (sockClient, out.c_str(), out.length(), 0);
        log->log("HNNetworking::sendVSPack()", "Sent: " + out, Log::D);
    }

}

std::string HNNetworking::packValue(int id){
    struct valueInstance vI = vSRef_->getValueInstance(id);
    std::string ret;
    ret += "<" + vI.driverName + "><" + to_string(vI.driverId) + "><";
    ret += vI.valueName + "><" + vI.valueUnit + "><";
    ret += vI.valueType + "><" + to_string(vI.valueId) + "><";
    ret += vI.value + "><" + vI.valueDataType + ">";
    return ret;
}

