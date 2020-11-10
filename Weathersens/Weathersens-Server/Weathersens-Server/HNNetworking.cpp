#include "HNNetworking.h"

HNNetworking::HNNetworking(WSValueserver* ref)
{
    vSRef_ = ref;
}

void HNNetworking::runNetwork(){
    using namespace std;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    int port = 8090;
    if (sock < 0)
    {
        cout << "Erronr in creating socket" << endl;
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
        cout << "Error in binding server!" << endl;
    }

    if (listen(sock, 5) == -1)
    {
        cout << "Error in listening" << endl;
    }

    struct sockaddr_in client;
    int sock2;
    socklen_t len;
    char buffer[1024] = { 0 };

    while (true){
        bool isConnected = false;
        len = sizeof(client);
        sock2 = accept(sock, (struct sockaddr*) & client, &len);
        if (sock2 < 0)
        {
            cout << "Error in connecting to client!" << endl;
        }
        else
        {
            isConnected = true;
            std::string msg;
            int lenmsg = recv(sock2, buffer, 1024, 0);
            cout << "Message incoming in loop entry (len: " << lenmsg << "): ";
            for (int i = 0; i < lenmsg; i++)
            {
                cout << buffer[i];
                msg += buffer[i];
            }
            cout << endl;
            sendVSPack(sock2, msg);
            isConnected = false;
            close(sock2);
        }
    }
}

void HNNetworking::sendVSPack(int sockClient, std::string msg){
    if(msg.find("@va") <= msg.length()){
        cout << "Syncing whole dataset!" << endl;
        std::string buf;
        for (int i = 0; i < vSRef_->getValueCount(); i++){
            buf += this->packValue(i) + "\n";
        }
        send(sockClient, buf.c_str(), buf.length(), 0);
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

