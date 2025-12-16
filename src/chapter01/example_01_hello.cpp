#include <iostream>
#include <thread>

static void hello_concurrent() {
    std::cout << "Hello Concurrent" << std::endl;
}

int main() {
    std::thread t(hello_concurrent);
    t.join();
    
    return 0;
}