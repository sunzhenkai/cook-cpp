#include "sys/socket.h"
#include "study/socket/basic/server.h"
#include <cstdlib>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port) : port(port) {}

void Server::Start() {
    // 1. create socket
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("create socket failed");
        exit(EXIT_FAILURE);
    }
    // 2. set socket options
    if (setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &socket_opt, sizeof(socket_opt))) {
        perror("setsockopt failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    // 3. bind
    if (bind(socket_fd, (struct sockaddr *) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // 4. listen
    if (listen(socket_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    // 5. accept
    accept_thread = std::thread(Server::Accept, nullptr);
}

Server::~Server() {
    if (socket_fd != 0) {
        close(socket_fd);
    }
}

void Server::Accept(void *args) {

}