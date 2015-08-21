#include <iostream>
#include <memory>
#include "lazy.hh"

using namespace std;

struct BigObject {
    BigObject() {
        cout << "lazy load big object" << endl;
    }
};

struct MyStruct {
    MyStruct() {
        obj = lazy([]{ return std::make_shared<BigObject>(); });
    }

    void load() { obj.value(); }

    Lazy<std::shared_ptr<BigObject>> obj;
};

int foo(int x) { 
    return x*2; 
}

void test_lazy() {
    int y = 4;
    auto lazyer1 = lazy(foo, y);
    
    auto lazyer2 = lazy([]{
        return 16; 
    });

    auto f = [] (int x) {
        return x + 16;
    };
    auto lazyer3 = lazy(f, 16);

    MyStruct t;

    cout << lazyer1.value() << endl;
    cout << lazyer2.value() << endl;
    cout << lazyer3.value() << endl;
    t.load();
}


int main() {
    test_lazy();
}
