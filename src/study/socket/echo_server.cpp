#include "study/socket/basic/server.h"
#include "iostream"
#include "cstring"

#define BUFFER_SIZE 1024
class EchoServer : public SocketServer {
public:
    explicit EchoServer(int port) : SocketServer(port) {}
    void Process(int socket_fd) override {
        char buffer[BUFFER_SIZE + 1] = {0};
        read(socket_fd, buffer, BUFFER_SIZE);
        printf("[SERVER] received. [socket_fd=%d, data=%s]\n", socket_fd, buffer);
        send(socket_fd, buffer, strlen(buffer), 0);
    }
};

int main() {
    EchoServer es(8080);
    es.Start();
    es.Join();
    return 0;
}
