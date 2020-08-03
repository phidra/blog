#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <atomic>

void computer_task(char letter,
                   size_t nb_of_ticks,
                   std::queue<char>& data_to_write,
                   const unsigned long long amount,
                   std::mutex& m,
                   std::condition_variable& cv);
void displayer_task(const std::string& initial_string,
                    const std::atomic<bool>& is_finished,
                    std::queue<char>& data_to_write,
                    std::mutex& m,
                    std::condition_variable& cv);
