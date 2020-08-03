#include <iostream>
#include <sstream>
#include <thread>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

#include "workers.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << endl;
        cerr << "USAGE: " << argv[0] << "  AMOUNT" << endl;
        cerr << endl;
        return 1;
    }

    // base_amount = how much computation each thread has to make (adapt this to the power of your computer) :
    const unsigned long long base_amount = stoull(argv[1]);

    constexpr const size_t half_length = 20;
    string initial_string(2 * half_length, '-');

    // communication between threads :
    queue<char> data_to_write;
    mutex m;
    condition_variable cv;
    atomic<bool> is_finished{false};

    // displayer thread runs in background :
    auto displayer = thread(displayer_task, cref(initial_string), cref(is_finished), ref(data_to_write), ref(m), ref(cv));

    // computer tasks run in foreground, sequentially :
    computer_task('A', half_length, data_to_write, base_amount, m, cv);
    computer_task('B', half_length, data_to_write, base_amount, m, cv);

    {
        lock_guard<mutex>{m};
        is_finished.store(true);
    }
    cv.notify_one();
    displayer.join();

    return 0;
}
