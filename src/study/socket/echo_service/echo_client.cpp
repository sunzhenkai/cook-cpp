#include "study/socket/basic/client.h"
#include "thread"
#include "chrono"

using namespace std::literals;

int main() {
    SocketClient client("127.0.0.1", 8080);
    client.Connect();
    client.Send("hello world");
    std::this_thread::sleep_for(60s);
    client.Disconnect();
    return 0;
}