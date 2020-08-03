#include <iostream>
#include <string>
#include <thread>

void heavy_task(int& result, const int amount)
{
    // FAST : working on a local accumulator, and only setting the result in the end :
    int acc = 0;
    for (int i = 0; i < amount; ++i)
    {
        (i % 2 == 0) ? acc += 3 : acc -= 2;
    }
    result = acc;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "USAGE: " << argv[0] << "  AMOUNT" << std::endl;
        return 1;
    }

    const int amount = std::stoi(argv[1]);
    int result_even = 0;
    int result_odd = 0;
    auto th = std::thread(heavy_task, std::ref(result_even), amount);
    heavy_task(result_odd, amount);
    th.join();

    return 0;
}
