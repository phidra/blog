#include <iostream>
#include <functional>
#include <thread>

// Cette POC montre qu'on ne peut pas se passer destd::ref pour threader une fonction qui attend un T&

void heavy_task(int& result)
{
    result = 499;
}

int main(void)
{
    int result = 0;

    // won't compile (actually needs an int& whereas an int is deduced) :
    // auto th = std::thread(heavy_task, result);  // wrong type

    auto th = std::thread(heavy_task, std::ref(result));

    th.join();
    std::cout << result << std::endl;
    return 0;
}
