// enable_if example: two ways of using enable_if
#include <iostream>
#include <type_traits>

// 1. the return type (bool) is only valid if T is an integral type:
template<class T>
typename std::enable_if<std::is_integral<T>::value, bool>::type
is_odd (T i) {
    return bool(i%2);
}

// 2. the second template argument is only valid if T is an integral type:
template<class T,
         class = typename std::enable_if<std::is_integral<T>::value>::type>
bool is_even (T i) {
    return !bool(i%2);
}

// 3. the second function argument is only valid if the first one is an
// integral type.
template<class T>
T foo(T t, typename std::enable_if<std::is_integral<T>::value, int>::type u = 0) {
    return t;
}

// use std::enable_if to implement overload
template<class T>
typename std::enable_if<std::is_integral<T>::value, int>::type
bar(T t) {
    std::cout << t << std::endl;
    return 1;
}

template<class T>
typename std::enable_if<std::is_same<T, std::string>::value, int>::type
bar(T t) {
    std::cout << t << std::endl;
    return 0;
}


int main() {
    short int i = 1;    // code does not compile if type of i is not integral
    std::cout << std::boolalpha;
    std::cout << "i is odd: " << is_odd(i) << std::endl;
    std::cout << "i is even: " << is_even(i) << std::endl;
    //std::cout << is_even(1.5) << std::endl;   // compile error

    foo(1);
    foo(1, 2);
    //foo(2.5);    // compile error
    //foo(2.5, 3); // compile error

    bar(700);
    bar(std::string("Hello, c++11!"));
    //bar(&i);      // compile error

    return 0;
}

