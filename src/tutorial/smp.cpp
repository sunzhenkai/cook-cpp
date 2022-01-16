#include "seastar/core/app-template.hh"
#include "seastar/core/reactor.hh"
#include "iostream"

using namespace std;

int main(int argc, char **argv) {
    seastar::app_template app;
    auto r = [] {
        cout << "smp::count = " << seastar::smp::count << "\n";
        return seastar::make_ready_future<int>(0);
    };

    return app.run(argc, argv, std::move(r));
}