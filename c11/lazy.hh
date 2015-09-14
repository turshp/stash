/**
 * lazy initialization from C#.
 * Lazy initialization of an object means that its creation is deferred until
 * it is first used. Lazy initialization is primarily used to improve
 * performance, avoid wasteful computation, and reduce program memory
 * requirements.
 */
#include <utility>
#include <functional>
#include "optional.hh"

template<typename T>
class Lazy {
public:
    Lazy() {}

    template<typename Func, typename... Args>
    Lazy(Func&& func, Args&&... args) {
        // use a lambda to save args, so _func will have no arguments.
        _func = [&func, &args...] () { return func(args...); };
        // or use std::bind
        //_func = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
    }

    // save the result in Optional.  
    const T& value() {
        if (!_value) {
            _value = _func();
        }

        return *_value;
    }

    bool is_value_created() const { return _value.is_init(); }
private:
    std::function<T()> _func;
    Optional<T> _value;
};

template<typename Func, typename... Args>
Lazy<typename std::result_of<Func(Args...)>::type>
lazy(Func&& fun, Args&& ... args) {
    return Lazy<typename std::result_of<Func(Args...)>::type>(
        std::forward<Func>(fun), std::forward<Args>(args)...);
}
