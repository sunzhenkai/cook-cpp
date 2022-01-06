#include <iostream>
#include <boost/preprocessor.hpp>
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/tuple/size.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#include "boost/preprocessor/control/if.hpp"
#include "boost/preprocessor/control/iif.hpp"

using namespace std;

#define DN_SEQ ((1, 2))((2, 3, 4))
#define D_TUPLE (1, 2, 3)

#define TUPLE_SIZE(r, data, elem) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_SIZE(elem))
#define PRINT_TUPLE_SIZE(unused, data, elem)    \
    std::cout << BOOST_PP_TUPLE_SIZE(elem) << std::endl;
#define CAT_TUPLE(unused, data, elem) \
    BOOST_PP_STRINGIZE(BOOST_PP_CAT(9, BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE, 0, elem)))

int main() {
    cout << BOOST_PP_TUPLE_ELEM(0, D_TUPLE) << endl;
    cout << BOOST_PP_TUPLE_SIZE(D_TUPLE) << endl;
    cout << BOOST_PP_TUPLE_SIZE(D_TUPLE) + BOOST_PP_SEQ_ELEM(0, DN_SEQ) << endl;

    BOOST_PP_SEQ_FOR_EACH(PRINT_TUPLE_SIZE, , DN_SEQ)
    cout << BOOST_PP_SEQ_FOR_EACH(TUPLE_SIZE, _, DN_SEQ) << endl;
    cout << BOOST_PP_SEQ_FOR_EACH(CAT_TUPLE, , DN_SEQ) << endl;
    cout << BOOST_PP_CAT(1, 2) << endl;
    return 0;
}