#include <functional>
#include <type_traits>

// class template declaration
template<typename T>
class Task;

// template specialization, means T=R(Args...)
template<typename R, typename... Args>
class Task<R(Args...)> {
public:
    Task(std::function<R(Args...)>&& f):
        _fun(std::move(f)) {}

    Task(std::function<R(Args...)>& f):
        _fun(f) {}

    R run(Args&&... args) {
        return _fun(std::forward<Args>(args)...);
    }


    /**
     * Task save a function T whose signature is R(Args...), and call then()
     * will get another Task, who also save a function, who take R as the 
     * only argument, but it don't get R until call run().
     *
     * For example:
     *     int foo(int, double);
     *     int bar(int);
     *     auto task = Task<int(int, double)>(foo).then(bar);
     * task's type would be Task<int(int, double)>, you can get the result:
     *     auto ret = task.run(1, 1.5);
     * 
     */
    template<typename F>
    auto then(F&& f)->Task<typename std::result_of<F(R)>::type(Args...)> {
        // get return type of F
        using ret_type = typename std::result_of<F(R)>::type;
        
        auto func = std::move(_fun);
        
        return Task<ret_type(Args...)>([func, &f](Args&& ... args){
            return f(func(std::forward<Args>(args)...));
        });
    }

private:
    std::function<R(Args...)> _fun;
};
