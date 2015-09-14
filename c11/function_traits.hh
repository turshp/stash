/**
 * A traits class to get function type, return type, arguments number and
 * argument type
 */
#include <functional>
#include <tuple>


// declaration of function_traits
template<typename T>
struct function_traits;


// class specialization with return type and arguments.
template<typename R, typename... Args>
struct function_traits<R(Args...)> {
    enum {
        arity = sizeof...(Args)
    };

    typedef R (function_type) (Args...);
    typedef R return_type;
    using stl_function_type = std::function<function_type>;
    typedef R(*pointer) (Args...);

    template<size_t I>
    struct args {
        static_assert(I < arity, "index is out of range,\
            index must less than sizeof Args");
        using type = typename std::tuple_element<I, std::tuple<Args...>>::type;
    };
};

// for function pointer. Derived from first one.
template<typename R, typename... Args>
struct function_traits<R(*)(Args...)>:function_traits<R(Args...)> {};

// for std::function
template<typename R, typename... Args>
struct function_traits<std::function<R(Args...)>>:function_traits<R(Args...)> {};

// for member function
// about identifier __VA_ARGS__, check out in
// https://en.wikipedia.org/wiki/Variadic_macro
#define FUNCTION_TRAITS(...) \
    template<typename R, typename ClassType, typename... Args> \
    struct function_traits<R(ClassType::*)(Args...) __VA_ARGS__>:\
        function_traits<R(Args...)> {};

FUNCTION_TRAITS()
FUNCTION_TRAITS(const)
FUNCTION_TRAITS(volatile)
FUNCTION_TRAITS(const volatile)

// for function object
template<typename Callable>
struct function_traits:function_traits<decltype(&Callable::operator())> {};

