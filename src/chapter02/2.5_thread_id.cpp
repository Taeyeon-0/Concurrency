#include <thread>
#include <iostream>

void print_thread_id() {
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::thread t1(print_thread_id);
    std::thread t2(print_thread_id);
    t1.join();
    t2.join();
    return 0;
}
