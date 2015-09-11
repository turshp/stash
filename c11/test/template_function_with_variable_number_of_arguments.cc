#include <iostream>

using namespace std;

// 1. 递归方式展开参数包
void print() {
    cout << endl;
}

template<class T, class... Args>
void print(T head, Args... rest) {
    cout << head << " ";
    print(rest...);
}

// 2. 利用逗号表达式和初始化列表的方式展开参数包
template<class T>
void printarg(T t) {
    cout << t << " ";
}

template<class... Args>
void expand(Args... args) {
    // 先计算第一个表达式，也就是调用函数printarg(),然后将第二个表达式的结果，
    // 也就是0作为整个表达式的结果
    std::initializer_list<int>{(printarg(args), 0)...};
    cout << endl;
}


int main() {
    print(1, 2, 3, 4, 5);
    expand(5, 4, 3, 2, 1);

    string s{"r2d2"};
    string s1{"c3po"};
    print("hello", s, 1 ,2);
    expand("Hello", s1, 3, 4);

    return 0;
}

