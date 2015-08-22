#include <iostream>
#include <string>
#include "task_chain.hh"

using namespace std;

void test_task() {
    Task<int(int)> task([](int i) {
        return i; 
    });

    auto result = task.then([](int i) { return i + 1; }
                     ).then([](int i) { return i * 2; }
                     ).then([](int i) { return i * 3; }
                     ).run(1);

    cout << "test case 1: " << endl;
    cout << result << endl << endl;
}

string foo(const string& a, const string& b) {
    cout << a << b << endl;
    return b;
}

string bar(const string& b) {
    cout << b << endl;
    return b + b;
}

void test_task2() {
    auto task = Task<string(string, string)>(foo).then(bar).then(bar).then(bar);
    cout << "test case 2:" << endl;
    cout << task.run("Hello, ", "I'm R2D2") << endl << endl;
}

int main() {
    test_task();
    test_task2();
}
