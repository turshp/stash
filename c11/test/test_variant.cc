#include <iostream>
#include <string>
#include "variant.hh"
#include "type_name.hh"

using namespace std;

void test_integer_max() {
    cout << "Maximum of <5> is: " << IntegerMax<5>::value << endl;
    cout << "Maxinum of <1,3,4,2,1,8>: "
         << IntegerMax<1, 3, 4, 2, 1, 8>::value << endl;
    cout << endl;
}

void test_contains() {
    cout << boolalpha;
    cout << "Contains int in <>: " << Contains<int>::value << endl;
    cout << "Contains int in <long, double, string, int, int*>: "
         << Contains<int, long, double, string, int, int*>::value << endl;
    cout << endl;
}

void test_indexof() {
    cout << "Index of int in <>: " << IndexOf<int>::value << endl;
    cout << "Index of long in <long, double, int>: "
         << IndexOf<long, long, double, int>::value << endl;
    cout << "Index of int in <long, double, int>: "
         << IndexOf<int, long, double, int>::value << endl;
    //cout << "Index of string in <long, double, int>: "
    //     << IndexOf<string, long, double, int>::value << endl;
    cout << endl;
}

void test_at() {
    cout << "Type name at index 0 in <int, long, double>: "
         << type_name<At<0, int, long, double>::type>() << endl;
    cout << "Type name at index 2 in <int, long, double>: "
         << type_name<At<2, int, long, double>::type>() << endl;
    cout << endl;
}

void test_variant()
{
    typedef Variant<int, double, string> cv;
    cv v;
    cout << "Type name at index 1 of cv: "
         << type_name<cv::IndexType<1>>() << endl;
    cout << "Index of string in cv: "
         << v.get_index_of<string>() << endl;
    cout << boolalpha;
    cout << "Is v empty: " << v.empty() << endl;
    cout << endl;

    cv v2 = string("Hello, I'm R2D2.");
    //cv v3 = "Hello, I'm 3PO.";  // compile error
    cv v4(v2);
    cv v5(std::move(v2));
    v = v4;
    v4 = std::move(v5);
    v = 10;
    
    cout << "Is v int: " << v.is<int>() << endl;
    cout << "Is v string: " << v.is<string>() << endl;
    cout << "Is v empty: " << v.empty() << endl;
    cout << "Type of v: " << v.type().name() << endl;
    cout << "Value of v: " << v.get<int>() << endl;
    try {
        cout << v.get<double>() << endl;
    } catch(bad_cast& e) {
        cout << "bad cast" << endl;
    }

    // 通过一组lambda访问vairant
    cout << endl;
    v4.visit([&](double i){cout << i << endl; },
            [&](short i){cout << i << endl; },
            [](int i){cout << i << endl; },
            [](string i){cout << i << endl; });
}


int main()
{
    test_integer_max();
    test_contains();
    test_indexof();
    test_at();
    test_variant();
}
