#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>

// Straightforward code à insérer dans le post.

int main(void)
{
    // vector<int&> v;  // won't compile
    int a=42, b=19;
    std::vector<std::reference_wrapper<int>> v{a, b};
    v[1] += 1000;
    std::cout << b;  // 1019
    return 0;
}

