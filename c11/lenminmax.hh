#include <type_traits>
#include <utility>

// get the type of the value any iterator points to
template<typename T>
using iterator_value_type = typename std::remove_reference<
    decltype(*std::declval<T>())>::type;


// the second template parameter MinMaxType is just a type alias
template<typename ConstInputIterator,
         typename MinMaxType = iterator_value_type<ConstInputIterator>>
auto lenminmax(ConstInputIterator first, ConstInputIterator last)
    -> std::tuple<size_t, MinMaxType, MinMaxType> {
    using ret_type = std::tuple<size_t, MinMaxType, MinMaxType>;
    if (first == last) {
        return ret_type{0, 0, 0};
    }

    size_t count{1};
    auto min(*first);
    auto max(min);
    while(++first != last) {
        ++count;
        const auto& value = *first;
        if (value < min) {
            min = value;
        } else if (max < value) {
            max = value;
        }
    }

    return ret_type{count, min, max};
}

