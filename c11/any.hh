/**
 * From boost::any
 * Provides the class Any which, like JavaScript variables, can store
 * arbitrary types of information.
 */
#include <memory>
#include <typeindex>
#include <type_traits>


class Any {
public:
    Any(void):
        _tp_index(typeid(void)) {}

    Any(Any& that):
        _ptr(that.clone()),
        _tp_index(that._tp_index) {}

    Any(Any&& that):
        _ptr(std::move(that._ptr)),
        _tp_index(std::move(that._tp_index)) {} // can std::type_index move?

    // use std::decay to remove reference and cv-qualifier
    // so if the original type of U is same with type Any, will not allowed
    // to compile
    // but why do this?
    template<typename U, class = typename std::enable_if<
        !std::is_same<typename std::decay<U>::type, Any>::value, U>::type>
    Any(U&& value):
        _ptr(new Derived<typename std::decay<U>::type>(std::forward<U>(value))),
        _tp_index(typeid(typename std::decay<U>::type)) {}

    bool is_null() const {
        return !bool(_ptr);
    }

    template<typename U>
    bool is() const {
        return _tp_index == std::type_index(typeid(U));
    }

    template<typename U>
    U& any_cast() {
        if (!is<U>()) {
            throw std::bad_cast();
        }

        auto derived = dynamic_cast<Derived<U>*>(_ptr.get());
        return derived->_value;
    }

    Any& operator=(const Any& other) {
        if (_ptr == other._ptr) {
            return *this;
        }

        _ptr = other.clone();
        _tp_index = other._tp_index;
        return *this;
    }

private:
    struct Base;
    typedef std::unique_ptr<Base> BasePtr;

    struct Base {
        virtual ~Base() {};
        virtual BasePtr clone() const = 0;
    };

    template<typename T>
    struct Derived: Base {
        template<typename U>
        Derived(U&& value):
            _value(std::forward<U>(value)) {}

        BasePtr clone() const {
            return BasePtr(new Derived<T>(_value));
        }

        T _value;
    };


    BasePtr clone() const {
        if (_ptr) {
            return _ptr->clone();
        }

        return nullptr;
    }

private:
    BasePtr _ptr;
    std::type_index _tp_index;
};
