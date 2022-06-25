#include <tuple>
#include "iostream"

typedef std::tuple<int, int> R;

int pow(int v) {
    return v * v;
}

template<std::size_t I = 0, typename... Vs>
inline typename std::enable_if<I == sizeof...(Vs), void>::type PrintPP(std::tuple<Vs...> &t) {
    std::cout << std::get<I>(t) << std::endl;
    PrintPP<I + 1, Vs...>(t);
}

template<size_t... Vs>
void PrintSeq(std::index_sequence<Vs...>) {
    std::cout << sizeof...(Vs) << std::endl;
    auto tp = std::make_tuple(pow(Vs)...);
    std::cout << std::get<0>(tp) << ", " << std::get<1>(tp) << std::endl;
}

int main() {
    R r(1, 2);
    std::cout << std::get<1>(r) << std::endl;

    constexpr size_t nr = std::tuple_size<R>::value;
    auto seq = std::make_index_sequence<nr>{};
    PrintSeq(seq);
    return 0;
}