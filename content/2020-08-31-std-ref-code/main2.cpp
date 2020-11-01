#include <iostream>
#include <functional>

// C'était pas le bug à la base, mais cette POC montre qu'on ne peut pas bind sur une fonction template.
// (on peut contourner, mais c'était pas le but : https://stackoverflow.com/questions/14727313/c-how-to-reference-templated-functions-using-stdbind-stdfunction)

template <typename T, typename ValueType>
void add(T accumulator, ValueType value) {}

template <>
void add(int not_really_an_accumulator, int value) { std::cout << "not really adding : only displaying what value would be obtained : " << not_really_an_accumulator + value << std::endl; }

template <>
void add(int& accumulator, int value) { accumulator += value; std::cout << "adding AND displaying : " << accumulator << std::endl; }


int main(void)
{
    int x = 42;

    add<int, int>(x, 100);
    std::cout << "current value of x = " << x << std::endl;

    add<int&, int>(x, 100);
    std::cout << "current value of x = " << x << std::endl;

    // je ne peux pas bind sur une fonction template...
    /* auto add_to_x = std::bind(add, x, std::placeholders::_1); */
    /* add_to_x(100000); */
    /* std::cout << "current value of x = " << x << std::endl; */
    return 0;
}

