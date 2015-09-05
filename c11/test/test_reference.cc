#include <iostream>
#include "type_name.hh"

using namespace std;

template<class T>
void func(T&& t) {
    cout << type_name<T>() << endl;
}

int main() {
    string str = "test";
    func(str);
    func(move(str));

    return 0;
}
