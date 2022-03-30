#include "iostream"
#include "mongocxx/client.hpp"
#include "mongocxx/instance.hpp"
#include "mongocxx/uri.hpp"

int main() {
    mongocxx::instance instance{};
    mongocxx::uri uri("mongodb://192.168.6.6:27017");
    mongocxx::client client(uri);
    std::cout << "hello" << std::endl;
    return 0;
}