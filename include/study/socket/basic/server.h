#pragma once

#include <netinet/in.h>
#include "thread"

class Server {
public:
    explicit Server(int port);
    void Start();
    static void Accept(void *args);
    ~Server();
private:
    int port{0}, socket_fd{0}, socket_opt{1};
    struct sockaddr_in address;
    std::thread accept_thread;
};