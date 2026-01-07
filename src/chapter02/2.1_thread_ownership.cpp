#include <thread>
#include <iostream>

void some_function() {
    std::cout << "some_function running\n";
}
void some_other_function() {
    std::cout << "some_other_function running\n";
}

int main() {
    std::thread t1(some_function);            // 1
    std::thread t2 = std::move(t1);           // 2
    t1 = std::thread(some_other_function);    // 3
    std::thread t3;                           // 4
    t3 = std::move(t2);                       // 5
    // t1 = std::move(t3);                   // 6 (危险！)
    t1.join();
    t3.join();
    return 0;
}
