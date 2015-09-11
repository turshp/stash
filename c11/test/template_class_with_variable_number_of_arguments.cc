#include <typeinfo>
#include <string>
#include <tuple>
#include <iostream>
#include "type_name.hh"


// 递归的方式展开参数包
// MakeIndexes<3> ----> MakeIndexes<2, 2> ----> MakeIndexes<1,1,2>
// ----> MakeIndexes<0,0,1,2 >
template<int ...>
struct IndexSeq{};

template<int N, int ... Indexes>
struct MakeIndexes {
    using type = typename MakeIndexes<N-1, N-1, Indexes...>::type;
};

template<int ... Indexes>
struct MakeIndexes<0, Indexes...> {
    using type = IndexSeq<Indexes...>;
};

// 
template<typename T>
void Print(T t) {
    std::cout << t << std::endl;
}

template<typename T, typename... Args>
void Print(T t, Args ... args) {
    std::cout << t << ", ";
    Print(args...);
}

template<int ... Indexes, typename ... Args>
void print_helper(IndexSeq<Indexes...>, std::tuple<Args...>&& tup) {
    Print(std::get<Indexes>(tup)...);
}

template<typename ... Args>
void print(Args... args) {
    print_helper(typename MakeIndexes<sizeof...(Args)>::type(),
                 std::make_tuple(args...));
}



int main() {
    int a = 100;
    double b = 200.0;
    std::string c = "Jane Doe";
    print(a, b, c);

    using T = MakeIndexes<5>;
    std::cout << type_name<T>() << std::endl;
    std::cout << type_name<T::type>() << std::endl;
}
