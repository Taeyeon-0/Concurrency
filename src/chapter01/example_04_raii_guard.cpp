#include <iostream>
#include <thread>
#include <exception>

class thread_guard {
    std::thread& t;
public:
    explicit thread_guard(std::thread& t_): t(t_) {}
    
    ~thread_guard() {
        if(t.joinable()) {
            t.join();
            std::cout << "[Guard] Thread joined securely in destructor.\n";
        }
    }
    
    thread_guard(thread_guard const&)=delete;
    thread_guard& operator=(thread_guard const&)=delete;
};

void safe_function() {
    int local_state = 0;
    
    std::thread t([&local_state]{
        std::cout << "[Thread] Running...\n";
        local_state = 100; 
    });
    
    thread_guard g(t); // 无论下面是否抛出异常，g 析构时都会 join t
    
    // 模拟一段可能抛出异常的逻辑
    std::cout << "[Main] Doing risky work...\n";
    // throw std::runtime_error("Error occurred!"); // 取消注释可测试异常场景
}

int main() {
    try {
        safe_function();
    } catch(...) {
        std::cout << "Exception caught in main.\n";
    }
    return 0;
}