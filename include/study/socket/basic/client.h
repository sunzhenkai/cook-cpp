#pragma once

#include <string>
#include <netinet/in.h>
#include <unistd.h>

class SocketClient {
public:
    SocketClient(std::string host, int port);
    void Connect();
    void Send(const std::string &data);
    void Disconnect();
    ~SocketClient();
protected:
    std::string host;
    int port;
private:
    int socket_fd{0};
    struct sockaddr_in server_addr;
};