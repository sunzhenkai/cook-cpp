#include "study/socket/basic/client.h"
#include <arpa/inet.h>

SocketClient::SocketClient(std::string host, int port) : host(std::move(host)), port(port) {}

void SocketClient::Connect() {
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port); // convert host to network byte order
    if (inet_pton(AF_INET, host.c_str(), &server_addr.sin_addr) <= 0) {
        perror("invalid server address");
        exit(EXIT_FAILURE);
    }
    if (connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
        perror("connection failed");
        exit(EXIT_FAILURE);
    }
}

void SocketClient::Send(const std::string &data) {
    send(socket_fd, data.c_str(), data.size(), 0);
}

void SocketClient::Disconnect() {
    if (socket_fd != 0) {
        close(socket_fd);
        socket_fd = 0;
    }
}

SocketClient::~SocketClient() {
    Disconnect();
}