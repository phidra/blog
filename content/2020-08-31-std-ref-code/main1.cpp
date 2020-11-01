#include <iostream>
#include <functional>
#include <cassert>

// Cette POC montre qu'un T& est déduit en T, à moins :
//      - soit de préciser explicitement T& comme template-argument
//      - soit d'utiliser std::ref

template <typename T>
void add100(T x) { x += 100; }

int main(void)
{
    int a = 42;
    add100(a);  // KO : l'argument template est "int" (au lieu de int&)
    std::cout << a << std::endl;
    assert(a == 42);

    int& ref_to_a = a;
    add100(ref_to_a);  // KO aussi : l'argument template est "int" (au lieu de int&)
    std::cout << a << std::endl;
    assert(a == 42);

    add100<int&>(ref_to_a);  // OK : l'argument template est "int&"
    std::cout << a << std::endl;
    assert(a == 142);

    int b = 42;
    add100(std::ref(b));  // OK : l'argument template est "reference_wrapper<int>"
    std::cout << b << std::endl;
    assert(b == 142);
    return 0;
}
