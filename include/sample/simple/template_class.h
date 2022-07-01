#ifndef COOK_SEASTAR_TEMPLATE_CLASS_H
#define COOK_SEASTAR_TEMPLATE_CLASS_H

namespace simple {
    template<typename T>
    class TCls {
    public:
        void f();
    };

    class NonTCls {
    public:
        template<class T>
        void f();
    };
}

#endif //COOK_SEASTAR_TEMPLATE_CLASS_H
