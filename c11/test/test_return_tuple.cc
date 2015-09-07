#include <vector>
#include <iostream>
#include <tuple>
#include "lenminmax.hh"

using namespace std;

void test_lenminmax() {
    vector<int> vec{1,2,5,6,3,5,9,3,0,5,6};
    int min, max;
    tie(ignore, min, max) = lenminmax(vec.begin(), vec.end());
    cout << "minimum: " << min << endl;
    cout << "maximum: " << max << endl;
}

int main() {
    test_lenminmax();

    return 0;
}
