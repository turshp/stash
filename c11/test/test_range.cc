#include <iostream>
#include "range.hh"

using namespace std;

void test_range() {
    cout << "range(15):";
    for (int i : range(15)) {
        cout << " " << i;
    }
    cout << endl;

    cout  << "range(2,6):";
    for (auto i : range(2, 6)) {
        cout << " " << i;
    }
    cout << endl;

    cout << "range(2, 6, 3):";
    for (auto i : range(2, 6, 3)) {
        cout << " " << i;
    }
    cout << endl;

    cout << "range(-2, -6, -3):";
    for (auto i : range(-2, -6, -3)) {
        cout << " " << i;
    }
    cout << endl;

    cout << "range(10.5, 15.5):";
    for ( auto i : range(10.5, 15.5)) {
        cout << " " << i;
    }
    cout << endl;

    cout << "range(35, 27, -1):";
    for (int i : range(35, 27, -1)) {
        cout << " " << i;
    }
    cout << endl;
 
    cout << "range(2, 8, 0.5):";
    for (auto i : range(2, 8, 0.5)) {
       cout << " " << i;
    }
    cout << endl;

    cout << "range(8, 7, -0.1):";
    for (auto i : range(8, 7, -0.1)) {
       cout << " " << i;
    }
    cout << std::endl;

    cout << "range('a', 'z'):";
    for (auto i : range('a', 'z')) {
        cout << " " << i;
    }
    cout << std::endl;
}

int main(void) {
   test_range();
   return 0;
}

