#include <cstdlib>

#include <bsoncxx/builder/stream/array.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/types.hpp>

#include <bsoncxx/config/prelude.hpp>
#include "iostream"

using namespace bsoncxx;
using namespace builder::stream;

builder::stream::document BuildOne() {
    builder::stream::document build_doc;
    // {
    //     "_id" : 1,
    //     "name" : { "first" : "John", "last" : "Backus" },
    //     "contribs" : [ "Fortran", "ALGOL", "Backus-Naur Form", "FP" ],
    //     "awards" : [
    //                {
    //                  "award" : "W.W. McDowell Award",
    //                  "year" : 1967,
    //                  "by" : "IEEE Computer Society"
    //                },
    //                { "award" : "Draper Prize",
    //                  "year" : 1993,
    //                  "by" : "National Academy of Engineering"
    //                }
    //     ]
    // }
    build_doc << "_id" << 1 << "name" << open_document << "first"
              << "John"
              << "last"
              << "Backus" << close_document << "contribs" << open_array << "Fortran"
              << "ALGOL"
              << "Backus-Naur Form"
              << "FP" << close_array << "awards" << open_array << open_document << "award"
              << "W.W. McDowell Award"
              << "year" << 1967 << "by"
              << "IEEE Computer Society" << close_document << open_document << "award"
              << "Draper Prize"
              << "year" << 1993 << "by"
              << "National Academy of Engineering" << close_document << close_array;
    return build_doc;
}

int TestBson() {
    auto builder = BuildOne();
    auto doc = builder.view();

    // Once we have the document view, we can use ["key"] or [index] notation to reach into nested
    // documents or arrays.
    auto awards = doc["awards"];
    auto first_award_year = awards[0]["year"];
    auto second_award_year = doc["awards"][1]["year"];
    auto last_name = doc["name"]["last"];

    // If the key doesn't exist, or index is out of bounds, we get invalid elements.
    auto invalid1 = doc["name"]["middle"];
    auto invalid2 = doc["contribs"][1000];
    if (invalid1 || invalid2) {
        BSONCXX_UNREACHABLE;  // Not reached.
    }

    // Similarly, indexed access (either by string or numeric index) into a type that is not
    // a document or an array yields invalid eleemnts.

    auto invalid3 = doc["_id"]["invalid"];
    auto invalid4 = doc["name"][3];
    if (invalid3 || invalid4) {
        BSONCXX_UNREACHABLE;  // Not reached.
    }

    // test array
    auto arr_element = doc["contribs"];
    if (arr_element && arr_element.type() == bsoncxx::type::k_array) {
        bsoncxx::array::view arr(arr_element.get_array().value);
        std::cout << arr.length() << std::endl; // 67; not count of elements
        for (auto e: arr) {
//            std::cout << "E " << e.get_utf8().value.to_string() << std::endl;
        }
    }

    // Make all variables used.
    return (awards && first_award_year && second_award_year && last_name) ? EXIT_SUCCESS
                                                                          : EXIT_FAILURE;
}

// Type https://github.com/apache/orc/blob/main/c%2B%2B/test/TestType.cc
// Writer https://github.com/apache/orc/blob/main/c%2B%2B/test/TestWriter.cc
void TestBsonSchema() {
    auto builder = BuildOne();
    auto vw = builder.view();
    std::cout << vw.empty() << " - " << vw.length() << std::endl;
    for (auto it = vw.begin(); it != vw.end(); ++it) {
        std::cout << to_string(it->type()) << ": " << it->key()<< std::endl;
    }
}

void TestOrc() {
}

int main(int, char **) {
    TestBsonSchema();
}