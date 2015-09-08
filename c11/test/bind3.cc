#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using std::placeholders::_1;

int main() {
    std::vector<int> vec{1, 10, 15, 20, 3, 7, 8, 9, 2};
    // use bind
    auto f = std::bind(std::logical_and<bool>(),
                       std::bind(std::greater<int>(), _1, 5),
                       std::bind(std::greater<int>(), 10, _1));

    std::cout << std::count_if(vec.begin(), vec.end(), f) << std::endl;
    // use lambda
    std::cout << std::count_if(vec.begin(), vec.end(), [](int x) {
                               return x > 5 && x < 10;})  << std::endl;

    return 0;
}
