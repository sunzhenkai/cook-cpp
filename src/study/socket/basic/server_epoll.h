#pragma once
// ref: https://github.com/onestraw/epoll-example/blob/master/epoll.c#L102

class SocketServerEpoll {
public:
    explicit SocketServerEpoll(int port);

private:
    int port{0};
};