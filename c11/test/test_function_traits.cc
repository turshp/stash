#include <iostream>
#include <typeinfo>
#include <string>
#include <type_traits>
#include "function_traits.hh"


using namespace std;

template<typename T>
void print_type() {
    cout << typeid(T).name() << endl;
}

float (*castfunc) (string, int);
float free_function(const std::string& a, int b) {
    return (float) a.size()/b;
}

struct AA {
    int f(int a, int b) { return a+b; }
    int operator() (int) const { return 0; }
};

void test_function_traits() {
    std::function<int(int)> f = [](int a) { return a; };

    print_type<function_traits<std::function<int(int)>>::function_type>();
    print_type<function_traits<std::function<int(int)>>::args<0>::type>();

    print_type<function_traits<decltype(f)>::function_type>();
    print_type<function_traits<decltype(free_function)>::function_type>();
    print_type<function_traits<decltype(castfunc)>::function_type>();
    print_type<function_traits<AA>::function_type>();

    print_type<function_traits<decltype(&AA::f)>::function_type>();
    static_assert(
        std::is_same<function_traits<decltype(f)>::return_type, int>::value,
        "not same");

}

int main() {
    test_function_traits();
}
