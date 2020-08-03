#include <iostream>
#include <string>

void heavy_task(int& result, const int amount)
{
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
    int result_even = 0;
    int result_odd = 0;
    heavy_task(result_even, amount);
    heavy_task(result_odd, amount);

    return 0;
}
