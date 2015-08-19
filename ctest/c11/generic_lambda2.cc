#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v(10);

    std::iota(v.begin(), v.end(), 1);
    std::cout << "before sorted:" << std::endl;
    std::for_each(v.begin(), v.end(), [](auto i) {std::cout << i << " ";});
    std::cout << std::endl;

    std::sort(v.begin(), v.end(), [](auto i, auto j) { return (i > j);});
    std::cout << "after sorted:" << std::endl;
    std::for_each(v.begin(), v.end(), [](auto i) {std::cout << i << " ";});
    std::cout << std::endl;
}
