#include <iostream>
#include <functional>

using namespace std;

void func() {
    cout << __FUNCTION__ << endl;
}

class Foo {
public:
    static int foo_func(int a) {
        cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

class Bar {
public:
    int operator() (int a) {
        cout << __FUNCTION__ << "(" << a << ")->: ";
        return a;
    }
};

int main() {
    function<void(void)> fr1 = func; //绑定一个普通函数
    fr1();

    function<int(int)> fr2 = Foo::foo_func; // 绑定一个类静态成员函数
    cout << fr2(100) << endl;

    Bar bar;
    fr2 = bar;  // 绑定一个函数对象
    cout << fr2(200) << endl;

    return 0;
}
