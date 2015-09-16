/**
 * class variant from boost
 * The variant class template is a safe, generic, stack-based discriminated
 * union container, offering a simple solution for manipulating an object 
 * from a heterogeneous set of types in a uniform manner. Whereas standard
 * containers such as std::vector may be thought of as "multi-value, single
 * type," variant is "multi-type, single value."
 */
#include <typeindex>
#include <type_traits>
#include "function_traits.hh"

/**
 * Get max integer during compiling, for example:
 *   size_t max = IntegerMax<2, 1, 3, 5>::value;
 */
template<size_t... args>
struct IntegerMax;

template<size_t arg>
struct IntegerMax<arg>:std::integral_constant<size_t, arg> 
{
};

template<size_t arg, size_t... rest>
struct IntegerMax<arg, rest...>:
    std::integral_constant<size_t, 
                           (arg > IntegerMax<rest...>::value ?
                            arg : IntegerMax<rest...>::value)>
{
};

/**
 * Check if T contained in Types, for example:
 *   bool is_contained = Contains<int, long, float, std::string>::value;
 */
template<typename T, typename... Types>
struct Contains;

template<typename T>
struct Contains<T>:std::false_type
{
};

template<typename T, typename Head, typename... Rest>
struct Contains<T, Head, Rest...>:
    std::conditional<std::is_same<T, Head>::value,
                     std::true_type,
                     typename Contains<T, Rest...>::type>::type
{
};

/**
 * Get index of T during compiling, for example:
 *   int index = IndexOf<int, long, float, int, std::string>::value;
 */
template<typename T, typename... Types>
struct IndexOf;

template<typename T, typename... Rest>
struct IndexOf<T, T, Rest...>
{
    enum {value = 0};
};

// FIXME:
// if T is not in Types, return value could be wrong
template<typename T, typename Head, typename... Rest>
struct IndexOf<T, Head, Rest...>
{
    enum {value = (IndexOf<T, Rest...>::value + 1)};
};

template<typename T>
struct IndexOf<T>
{
    enum {value = -1};
};

/**
 * Get type of index, for example:
 *   At<1, int, float, double>::type x{};
 */
template<size_t index, typename... Types>
struct At;

template<typename T, typename... Rest>
struct At<0, T, Rest...>
{
    using type = T;
};

template<size_t index, typename Head, typename... Rest>
struct At<index, Head, Rest...>
{
    using type = typename At<index - 1, Rest...>::type;
};


template<typename... Types>
class Variant {
public:
    template<size_t index>
    using IndexType = typename At<index, Types...>::type;

    Variant():_type_index(typeid(void)) {}

    ~Variant()
    {
        destory(_type_index, &_data);
    }

    Variant(Variant<Types...>&& other): _type_index(other._type_index)
    {
        move(_type_index, &_data, &other._data);
    }

    Variant(const Variant<Types...>& other): _type_index(other._type_index)
    {
        copy(_type_index, &_data, &other._data);
    }

    /**
     * Notice that copy constructor requires exactly same type, but copy
     * operator don't.
     */
    Variant& operator=(Variant&& other)
    {
        destory(_type_index, &_data);
        _type_index = other._type_index;
        move(_type_index, &_data, &other._data);
        return *this;
    }

    Variant& operator=(const Variant& other)
    {
        destory(_type_index, &_data);
        _type_index = other._type_index;
        copy(_type_index, &_data, &other._data);
        return *this;
    }

    template<typename T, class = typename
        std::enable_if<Contains<typename std::decay<T>::type, Types...>::value>::type>
    Variant(T&& t): _type_index(std::type_index(typeid(void)))
    {
        using U = typename std::decay<T>::type;
        _type_index = std::type_index(typeid(U));
        new (&_data)U(std::forward<T>(t));
    }

    template<typename T>
    bool is() const
    {
        return (_type_index == std::type_index(typeid(T)));
    }

    bool empty() const
    {
        return is<void>();
    }

    std::type_index type() const
    {
        return _type_index;
    }

    template<typename T>
    typename std::decay<T>::type& get()
    {
        using U = typename std::decay<T>::type;
        if (!is<U>()) {
            throw std::bad_cast();
        }

        return *((U*)(&_data));
    }

    template<typename T>
    static int get_index_of()
    {
        return IndexOf<T, Types...>::value;
    }

    template<typename F>
    void visit(F&& f)
    {
        using T = typename function_traits<F>::template args<0>::type;
        if (is<T>()) {
            f(get<T>());
        }
    }

    template<typename F, typename... Rest>
    void visit(F&& f, Rest&&... rest)
    {
        using T = typename function_traits<F>::template args<0>::type;
        if (is<T>()) {
            visit(std::forward<F>(f));
        } else {
            visit(std::forward<Rest>(rest)...);
        }
    }

private:
    enum 
    {
        data_size = IntegerMax<sizeof(Types)...>::value,
        align_size = IntegerMax<alignof(Types)...>::value
    };
    using data_t = typename std::aligned_storage<data_size, align_size>::type;

    void destory(const std::type_index& id, void* data)
    {
        std::initializer_list<int>{(destory0<Types>(id, data), 0)...};
    }

    template<typename T>
    void destory0(const std::type_index& id, void* data)
    {
        if (std::type_index(typeid(T)) == id) {
            reinterpret_cast<T*>(data)->~T();
        }
    }

    void move(const std::type_index& id, void* new_d, void* old_d)
    {
        std::initializer_list<int>{(move0<Types>(id, new_d, old_d), 0)...};
    }

    template<typename T>
    void move0(const std::type_index& id, void* new_d, void* old_d)
    {
        if (std::type_index(typeid(T)) == id) {
            new (new_d)T(std::move(*reinterpret_cast<T*>(old_d)));
        }
    }

    void copy(const std::type_index& id, void* new_d, const void* old_d)
    {
        std::initializer_list<int>{(copy0<Types>(id, new_d, old_d), 0)...};
    }

    template<typename T>
    void copy0(const std::type_index& id, void* new_d, const void* old_d)
    {
        if (std::type_index(typeid(T)) == id) {
            new (new_d)T(*reinterpret_cast<const T*>(old_d));
        }
    }

private:
    data_t _data;
    std::type_index _type_index;
};

