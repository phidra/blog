#include <iostream>
#include <zlib.h>

int main(void)
{
    std::cout << "zlib version = " << zlibVersion() << std::endl;
    return 0;
}
