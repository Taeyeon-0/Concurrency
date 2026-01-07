#include <vector>
#include <thread>
#include <algorithm>
#include <iostream>

void do_work(unsigned id) {
    std::cout << "Thread " << id << " working\n";
}

int main() {
    std::vector<std::thread> threads;
    for (unsigned i = 0; i < 20; ++i) {
        threads.push_back(std::thread(do_work, i));
    }
    std::for_each(threads.begin(), threads.end(),
                  std::mem_fn(&std::thread::join));
    return 0;
}
