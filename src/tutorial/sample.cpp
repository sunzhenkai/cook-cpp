#include <seastar/core/app-template.hh>
#include <seastar/core/reactor.hh>
#include <iostream>

int main(int argc, char **argv) {
    seastar::app_template app;
    namespace bpo = boost::program_options;
    app.add_options()
            ("flag", "some optional flag")
            ("size,s", bpo::value<int>()->default_value(100), "size");
    app.add_positional_options({
                                       {"filename", bpo::value<std::vector<seastar::sstring>>()->default_value({}),
                                               "table files to verify", -1}
                               });
    app.run(argc, argv, [&app] {
        auto& args = app.configuration();
        if (args.count("flag")) {
            std::cout << "Flag is on\n";
        }
        std::cout << "Size is " << args["size"].as<int>() << "\n";
        auto& filenames = args["filename"].as<std::vector<seastar::sstring>>();
        for (auto&& fn : filenames) {
            std::cout << fn << "\n";
        }
        return seastar::make_ready_future<>();
    });
    return 0;
}