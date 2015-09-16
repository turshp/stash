#include<iostream>
#include<functional>
#include<exception>
#include "scope_guard.hh"

using namespace std;

void test_scope_guard()
{
    function<void()> f = []{ cout << "clean up from unnormal exit" << endl;};

    {
        cout << "Normal exit: " << endl;
        auto gd = make_guard(f);
        // ...
        gd.dismiss();
    }

    cout << endl;
    try {
        cout << "Exception been throwed: " << endl;
        auto gd = make_guard(f);
        throw exception();
    } catch (exception& e) {
        cout << "Exception been catched." << endl;
    }

    cout << endl;
    {
        cout << "Return early: " << endl;
        auto gd = make_guard(f);
        return;
        gd.dismiss();
    }
}

int main()
{
    test_scope_guard();
}
