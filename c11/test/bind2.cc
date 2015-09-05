#include <iostream>
#include <functional>

using namespace std;

struct A {
    int i_ = 0;

    void output(int a, int b) {
        cout << a << " " << b << endl;
        cout << "i_ = " << i_ << endl;
    }
};

int main() {
    A a;
    function<void(int, int)> fr = bind(&A::output, &a, placeholders::_1, placeholders::_2);
    a.i_ = 100;
    fr(1,2);

    function<int&(void)> fr_i = bind(&A::i_, &a);
    fr_i() = 123;
    cout << a.i_ << endl;

    return 0;
}
