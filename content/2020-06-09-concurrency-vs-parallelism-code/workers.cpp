#include <iostream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

using namespace std;

// heavy (but dummy) task to keep CPU busy
void _heavy_work(const unsigned long long amount) {
    unsigned long long unused_result = 0;
    for (int i = 0; i < amount; ++i) {
        unused_result += (i % 2 == 0) ? 3 : -2;
    }
}

void computer_task(char letter,
                   size_t nb_of_ticks,
                   queue<char>& data_to_write,
                   const unsigned long long amount,
                   mutex& m,
                   condition_variable& cv) {
    // repeatedly computes a heavy task then produce a char to write on the displayed string
    for (size_t x = 0; x < nb_of_ticks; ++x) {
        _heavy_work(amount);

        {
            lock_guard<mutex> lock(m);
            data_to_write.push(letter);
        }
        cv.notify_one();
    }
}

void displayer_task(const string& initial_string,
                    const atomic<bool>& is_finished,
                    queue<char>& data_to_write,
                    mutex& m,
                    condition_variable& cv) {
    string result{initial_string};
    size_t next_index_to_write = 0;
    while (!is_finished.load()) {
        // wait to be notified that there is something to write (or there is no more work to do) :
        unique_lock<mutex> lock(m);
        auto wakeup_predicate = [&data_to_write, &is_finished]() {
            return is_finished.load() || !data_to_write.empty();
        };
        cv.wait(lock, wakeup_predicate);

        // writes all the data to the result string :
        while (!data_to_write.empty()) {
            result[next_index_to_write++] = data_to_write.back();
            data_to_write.pop();
        }
        lock.unlock();

        // displays the written string :
        cout << "\r" << result << flush;  // might not work on windows/mac bc of EOL
    }
    cout << endl;
}
