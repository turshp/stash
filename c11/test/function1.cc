
void func() {}

struct Foo {
    void operator() (void) {}
};

struct Bar {
    using fr_t = void (*) ();
    static void func() {}

    operator fr_t() {
        return func;
    }
};

struct A {
    int a_;
    void mem_func() {}
};

int main() {
    void (* func_ptr) () = &func; // 函数指针
    func_ptr();

    Foo foo;    //仿函数
    foo();

    Bar bar;
    bar();      // 可被转换为函数指针的类对象

    void (A::*mem_func_ptr)() = &A::mem_func; // 类成员函数指针
    int A::*mem_obj_ptr = &A::a_;   // 类成员指针

    A aa;
    (aa.*mem_func_ptr)();
    aa.*mem_obj_ptr = 123;

    return 0;
}
