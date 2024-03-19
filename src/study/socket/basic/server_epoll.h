#pragma once

class SocketServerEpoll {
public:
    explicit SocketServerEpoll(int port);

private:
    int port{0};
};