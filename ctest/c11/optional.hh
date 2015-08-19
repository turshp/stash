#include <type_traits>
#include <utility>
#include <stdexcept>

template<typename T>
class Optional {
public:
    Optional():
        _has_init(false) {}
    Optional(const T& t) { create(t); }
    Optional(const Optional& other) {
        if (other.is_init()) {
            assign(other);
        }
    }
    ~Optional() { destory(); }

    template<typename... Args>
    void emplace(Args&&... args) {
        destory();
        create(std::forward<Args>(args)...);
    }

    bool is_init() const { return _has_init; }
    explicit operator bool() const { return is_init(); }
    const T& operator *() const {
        if (is_init()) {
            return *((T*)(&_data));
        }
        throw std::logic_error("is not init");
    }

private:
    template<typename... Args>
    void create(Args&&... args) {
        // placement new, call constructor of T, include copy constructor.
        new (&_data) T(std::forward<Args>(args)...);
        _has_init = true;
    }
    void destory() {
        if (_has_init) {
            _has_init = false;
            ((T*)(&_data))->~T();
        }
    }
    void assign(const Optional& other) {
        if (other.is_init()) {
            destory();
            // placement new, call copy constructor of T.
            // if here we use memcpy() would be any difference??
            new (&_data) T(*((T*)(&other._data))); 
            _has_init = true;
        } else {
            destory();
        }
    }

    using data_t = typename std::aligned_storage<sizeof(T), alignof(T)>::type;
private:
    data_t _data;
    bool _has_init;
};
