/**
 * Scrop guard for release resource safely.
 */

template<typename F>
class ScopeGuard {
public:
    // FIXME
    // Aren't F&& a universal reference? Then with the single constructor
    //  following, should include both rvalue and lvalue verion. But why
    //  this got compile failed?
    //explicit ScopeGuard(F&& f):
    //    _func(std::forward<F>(f)),
    //    _dismiss(false)
    //{
    //}

    explicit ScopeGuard(F&& f):
        _func(std::move(f)),
        _dismiss(false)
    {
    }

    explicit ScopeGuard(const F& f):
        _func(f),
        _dismiss(false)
    {
    }

    ~ScopeGuard()
    {
        if (!_dismiss && _func != nullptr) {
            _func();
        }
    }

    ScopeGuard(ScopeGuard&& rhs):
        _func(std::move(rhs._func)),
        _dismiss(rhs._dismiss)
    {
        rhs.dismiss();
    }

    void dismiss() {
        _dismiss = true;
    }
private:
    ScopeGuard();
    ScopeGuard(const ScopeGuard&);
    ScopeGuard& operator=(const ScopeGuard&);

private:
    F _func;
    bool _dismiss;
};


template<typename F>
ScopeGuard<typename std::decay<F>::type> make_guard(F&& f)
{
    return ScopeGuard<typename std::decay<F>::type>(std::forward<F>(f));
}

