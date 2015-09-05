#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

using std::placeholders::_1;

int main() {
    auto f = std::bind(std::logical_and<bool>(),
                       std::bind(std::greater<int>(), _1, 5),
                       std::bind(std::greater<int>(), 10, _1));

    std::vector<int> vec{1, 10, 15, 20, 3, 7, 8, 9, 2};

    std::cout << std::count_if(vec.begin(), vec.end(), f) << std::endl;

    return 0;
}
