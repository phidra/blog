#include <iostream>
#include <functional>
#include <cassert>

// Straightforward code à insérer dans le post.


template <typename T>
void pouet(T) {}

template <>
void pouet(int) { std::cout << "int" << std::endl; }

template <>
void pouet(int&) { std::cout << "int&" << std::endl; }


int main(void)
{
    int x = 42;
    int& ref_to_x = x;
    pouet(x);
    pouet(ref_to_x);
    pouet<int&>(ref_to_x);
}


