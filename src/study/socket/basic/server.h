#pragma once

#include <netinet/in.h>
#include "thread"

class SocketServer {
public:
    explicit SocketServer(int port);
    void Start();
    void Stop();
    void Join();
    static void Accept(void *args);
    virtual void Process(int socket_fd) = 0;
    ~SocketServer();
protected:
    int port{0};
private:
    int socket_fd{0}, socket_opt{1};
    struct sockaddr_in address;
    std::thread accept_thread;
    bool is_running{false};
};