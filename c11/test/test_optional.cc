#include <iostream>
#include <string>
#include "optional.hh"

struct MyStruct{
    MyStruct(int a=0, int b=0):
        _a(a),
        _b(b) {}

    int _a;
    int _b;
};

void test_optional() {
    Optional<std::string> a("KO");
    Optional<std::string> b("KO");
    Optional<std::string> c("aa");
    c = a;

    Optional<MyStruct> op;
    op.emplace(1, 2);
    MyStruct t;
    if (op) {
        t = *op;
    }

    std::cout << "a:" << t._a << ", b:" << t._b << std::endl;
    op.emplace(3, 4);
    t = *op;
    std::cout << "a:" << t._a << ", b:" << t._b << std::endl;
}


int main() {
    test_optional();
}
