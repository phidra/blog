#include <iostream>
#include <sstream>
#include <thread>

void heavy_task(int& result, const int amount)
{
    // FAST : alignment constraint ensures to avoid false sharing.
    for (int i = 0; i < amount; ++i)
    {
        (i % 2 == 0) ? result += 3 : result -= 2;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "USAGE: " << argv[0] << "  AMOUNT" << std::endl;
        return 1;
    }

    const int amount = std::stoi(argv[1]);
    int result_even __attribute__ ((aligned (64))) = 0;
    int result_odd __attribute__ ((aligned (64))) = 0;
    auto th = std::thread(heavy_task, std::ref(result_even), amount);
    heavy_task(result_odd, amount);
    th.join();

    return 0;
}
