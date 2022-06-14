#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include "seastar/net/api.hh"
#include "seastar/core/distributed.hh"
#include <iostream>

class Service {
public:
    void f() {
        std::cout << "run f" << std::endl;
    }
};

int main() {
    seastar::app_template app;
    static seastar::distributed<Service> service;
    char *av[5] = {"--overprovisioned", "-c", "4", "--blocked-reactor-notify-ms", "10"};
    return app.run(sizeof av / sizeof *av, av, [&]() {
        return service.start().then([&]() {
            return service.invoke_on_all(&Service::f);
        }).then([&] {
            service.stop();
        });
    });
}