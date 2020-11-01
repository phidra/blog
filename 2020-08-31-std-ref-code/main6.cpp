#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
// This POC shows that a vector of references won't compile (but a vector of reference_wrapper will) :

int main(void)
{
    // vector<int&> v;  // won't compile
    int a = 42;
    int b = 19;
    vector<reference_wrapper<int>> v{a, b};

    cout << "AVANT : a = " << a << endl;
    cout << "AVANT : b = " << b << endl;

    // applying a lambda that mutates the elements of the vector :
    auto add100 = [](int& x) { x += 100;};
    for_each(v.begin(), v.end(), add100);

    // directly mutating an element :
    v[0] += 2000;

    cout << "APRES : a = " << a << endl;
    cout << "APRES : b = " << b << endl;
    return 0;
}

