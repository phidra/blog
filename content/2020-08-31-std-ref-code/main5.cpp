#include <iostream>
#include <functional>


void add(int& accumulator, int value) { accumulator += value; }
using AddType = void (*)(int&, int);

// L'objectif de cette POC était d'essayer de spécialiser explicitement std::bind pour se passer de std::ref / std::reference_wrapper et
// que la fonction bindée utilise tout de même une référence
// TL;DR : ça ne marche que si l'argument est un std::reference_wrapper


int main(void)
{
    int x = 42;

    add(x, 100);
    std::cout << "STEP0> current value of x = " << x << std::endl;

    // classic bind with std::ref
    auto add_to_x = std::bind(&add, std::ref(x), std::placeholders::_1);
    add_to_x(100);
    std::cout << "STEP1> current value of x = " << x << std::endl;

    // DOES NOT WORK : attempt to explicitly bind with reference
    auto NOT_add_100_to_x = std::bind<AddType, int&, int>(&add, x, 100);
    NOT_add_100_to_x();
    std::cout << "STEP2> current value of x = " << x << std::endl;

    // WORKS : explicitly bind with reference_wrapper :
    auto add_100_to_x = std::bind<AddType, std::reference_wrapper<int>, int>(&add, x, 100);
    add_100_to_x();
    std::cout << "STEP3> current value of x = " << x << std::endl;

    // hum : d'après la doc : https://en.cppreference.com/w/cpp/utility/functional/bind
    // c'est si l'argument est de type reference_wrapper<T> qu'il est passé par référence à la fonction...
    // ça a l'air d'être codé en dur dans la lib, d'où le fait que ma STEP2 ne marche pas...
    // EDIT : je confirme : il y a une template-specialization en dur dans la libstdc++ :
    // https://github.com/gcc-mirror/gcc/blob/160061ac10f9143d9698daac5f7e46b5a615825c/libstdc%2B%2B-v3/include/std/functional#L296

    return 0;
}

