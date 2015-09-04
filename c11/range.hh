#include <stdexcept>

namespace detail_range {

template <typename T>
class Iterator {
public:
    using value_type = T;
    using size_type = size_t;

    Iterator(size_type cur_start, value_type begin_val, value_type step_val):
        cursor_(cur_start),
        step_(step_val),
        value_(begin_val) 
    {
        value_ += (step_ * cursor_);
    }

    value_type operator*() const {
        return value_;
    }

    bool operator!=(const Iterator& rhs) const {
        return (cursor_ != rhs.cursor_);
    }

    Iterator& operator++() {
        value_ += step_;
        ++cursor_;
        return (*this);
    }

private:
    size_type cursor_;
    const value_type step_;
    value_type value_;
};


template<typename T>
class Impl {
public:
    using value_type = T;
    using iterator = const Iterator<value_type>;
    using const_iterator = const Iterator<value_type>;
    using size_type = typename iterator::size_type;

    Impl(value_type begin_val, value_type end_val, value_type step_val):
        begin_(begin_val),
        end_(end_val),
        step_(step_val),
        max_count_(get_ajusted_count()) {}

    size_type size() const { return max_count_; }

    const_iterator begin() const { 
        return { 0, begin_, step_ };
    }
    const_iterator end() const {
        return { max_count_, begin_, step_ };
    }


private:
    size_type get_ajusted_count() const {
        if (step_ > 0 && begin_ >= end_) {
            throw std::logic_error(
                "End value must be greater than begin value");
        } else if (step_ < 0 && begin_ <= end_) {
            throw std::logic_error(
                "End value must be less than begin value");
        }

        size_type x = static_cast<size_type>((end_ - begin_)/step_);
        if (begin_ + (x * step_) != end_) {
            ++x;
        }

        return x;
    }

private:
    const value_type begin_;
    const value_type end_;
    const value_type step_;
    const size_type max_count_;
};

} // namespace detail_range


template<typename T>
detail_range::Impl<T> range(T end) {
    return { {}, end, 1};
}

template<typename T>
detail_range::Impl<T> range(T begin, T end) {
    return { begin, end, 1};
}

template<typename T, typename U>
auto range(T begin, T end, U step) 
    -> detail_range::Impl<decltype(begin + step)> {
    // maybe narrowing
    using r_t = detail_range::Impl<decltype(begin + step)>;
    return r_t(begin, end, step);
}

