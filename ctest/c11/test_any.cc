#include <iostream>
#include <string>
#include "any.hh"

using namespace std;

void test_any() {
    Any n;
    cout << std::boolalpha << "n is NUll:" << n.is_null() << endl;
    const string s1 = "hello";
    n = s1;
    try {
        n.any_cast<int>();
    } catch (bad_cast& e) {
        cout << e.what() << endl;
    }

    Any n1 = 1;
    cout << "n1 is int:" << n1.is<int>() << endl;

    Any n2 = s1;
    n2.any_cast<string>() = "hello, 3PO";
    cout << "n2:" << n2.any_cast<string>() << endl;

    const Any n3 = 1;
    n2 = n3;
    // Any n4 = n3;  // compile failed
}

int main() {
    test_any();
}
