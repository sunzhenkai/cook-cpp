#ifndef COOK_SEASTAR_CPP_H
#define COOK_SEASTAR_CPP_H

namespace basic {
    // define in header file, init in source file
    extern int i;
    extern const int ci;
    static int si;
//    static const int sci;

    class BC {
    public:
        int i;
        int ci;
        static const int sci;
    };
}

#endif //COOK_SEASTAR_CPP_H
