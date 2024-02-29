#include <iostream>
#include <vector>
#include <boost/preprocessor.hpp>
#include "boost/preprocessor/tuple/elem.hpp"
#include "boost/preprocessor/cat.hpp"
#include "boost/preprocessor/tuple/size.hpp"
#include "boost/preprocessor/seq/for_each.hpp"
#include "boost/preprocessor/control/if.hpp"
#include "boost/preprocessor/control/iif.hpp"
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

using namespace std;

#define DN_SEQ ((1, 2))((2, 3, 4))
#define D_TUPLE (1, 2, 3)

#define TUPLE_SIZE(r, data, elem) BOOST_PP_STRINGIZE(BOOST_PP_TUPLE_SIZE(elem))
#define PRINT_TUPLE_SIZE(unused, data, elem)    \
    std::cout << BOOST_PP_TUPLE_SIZE(elem) << std::endl;
#define CAT_TUPLE(unused, data, elem) \
    BOOST_PP_STRINGIZE(BOOST_PP_CAT(9, BOOST_PP_TUPLE_ELEM(BOOST_PP_TUPLE_SIZE, 0, elem)))

void TA() {
    cout << BOOST_PP_TUPLE_ELEM(0, D_TUPLE) << endl;
    cout << BOOST_PP_TUPLE_SIZE(D_TUPLE) << endl;
    cout << BOOST_PP_TUPLE_SIZE(D_TUPLE) + BOOST_PP_SEQ_ELEM(0, DN_SEQ) << endl;

    BOOST_PP_SEQ_FOR_EACH(PRINT_TUPLE_SIZE, , DN_SEQ)
    cout << BOOST_PP_SEQ_FOR_EACH(TUPLE_SIZE, _, DN_SEQ) << endl;
    cout << BOOST_PP_SEQ_FOR_EACH(CAT_TUPLE, , DN_SEQ) << endl;
    cout << BOOST_PP_CAT(1, 2) << endl;
}

//#define FS  \
//    ((fa, ((1, sa)(5, sb)(10, sc))) \
//    ((fb, ((1, sa)(5, sb)(10, sc))) \
//    ((fc, ((1, sa)(5, sb)(10, sc)))
//struct TbC {
//#define MACRO_EXPAND_TIME(r, data, elem) BOOST_PP_STRINGIZE(r)
//
//        // std::string BOOST_PP_CAT(BOOST_PP_TUPLE_ELEM(0, elem), BOOST_PP_TUPLE_ELEM(1, elem));
//    // elem: (fa, ((1, sa)(5, sb)(10, sc))
//#define MACRO_EXPAND_FIELD(r, elem) \
//        MACRO_EXPAND_TIME(r,  BOOST_PP_TUPLE_ELEM(0, elem), BOOST_PP_TUPLE_ELEM(1, elem))
//
//    BOOST_PP_SEQ_FOR_EACH_PRODUCT(MACRO_EXPAND_FIELD, FS);
//#undef MACRO_EXPAND_FIELD
//#undef MACRO_EXPAND_TIME
//};

void TB() {



// 假设我们有一个二维的预处理器序列，例如：
#define TWO_DIMENSIONAL_SEQ ((1, (1, 2)), (2, (3, 4)))

// 定义一个用于一维数组遍历的宏
#define ROW_PROCESSING(r, data, row_tuple) \
    BOOST_PP_SEQ_FOR_EACH(I, COLUMN_PROCESSING, BOOST_PP_TUPLE_ELEM(1, row_tuple))

// 定义一个用于单个元素遍历的宏
#define COLUMN_PROCESSING(r, data, col) \
    BOOST_PP_TUPLE_ELEM(0, data) "[" #col "] = " BOOST_PP_TUPLE_ELEM(1, row_tuple) "[" #col "];"

// 主体宏，用于展开二维序列
#define EXPAND_TWO_DIMENSIONAL_SEQ(matrix_name) \
    BOOST_PP_SEQ_FOR_EACH_I(ROW_PROCESSING, matrix_name, TWO_DIMENSIONAL_SEQ)

// 使用
//    std::vector<std::vector<int>> Matrix;
//    EXPAND_TWO_DIMENSIONAL_SEQ(Matrix)
//    TbC tbc;
}

#define SIMPLE_SEQ (a)(b)(c)

void TC() {
#define MACRO(r, data, elem) BOOST_PP_STRINGIZE(r) BOOST_PP_STRINGIZE(data) BOOST_PP_STRINGIZE(elem)
    std::string v = BOOST_PP_SEQ_FOR_EACH(MACRO, _, SIMPLE_SEQ);
#undef MACRO
    std::cout << v << std::endl;
}

int main() {
    TB();
//    TC();
    return 0;
}