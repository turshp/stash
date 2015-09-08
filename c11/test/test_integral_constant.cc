#include <iostream>

template<class T, T v>
struct IntegralConstant {
    static constexpr T value = v;
    typedef T value_type;
    constexpr operator T() const noexcept { return v; }
    constexpr T operator ()() const noexcept { return v; }
};

template <unsigned n>
struct factorial:IntegralConstant<int, n * factorial<n-1>::value> {};

template <>
struct factorial<0>:IntegralConstant<int,1> {};

int main() {
  std::cout << factorial<5>::value << std::endl;  // constexpr (no calculations on runtime)
  return 0;
}
