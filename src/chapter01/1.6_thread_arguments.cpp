#include <iostream>
#include <thread>
#include <string>
#include <memory>
#include <functional>

// 场景 1: 避免隐式转换带来的悬空指针
void print_string(int id, const std::string &s) {
    std::cout << "[Thread " << id << "] String content: " << s << std::endl;
}

// 场景 2: 引用传递
void increment_data(int& data) {
    data++;
    std::cout << "[Thread Ref] Incremented data to: " << data << std::endl;
}

// 场景 3: 类成员函数
class Worker {
public:
    void do_work(int loops) {
        for (int i = 0; i < loops; ++i) {
            std::cout << "[Worker] Working... " << i + 1 << std::endl;
        }
    }
};

// 场景 4: 移动语义 (Unique Ptr)
struct BigData {
    int value;
    BigData(int v) : value(v) { std::cout << "BigData Constructed.\n"; }
    ~BigData() { std::cout << "BigData Destroyed.\n"; }
};

void process_unique_ptr(std::unique_ptr<BigData> ptr) {
    std::cout << "[Thread Move] Owns BigData with value: " << ptr->value << std::endl;
}

int main() {
    // --- 1. 安全的字符串传递 ---
    char buffer[] = "Hello from buffer";
    // 显式转换为 string，避免传递 char* 指针导致潜在的生命周期问题
    std::thread t1(print_string, 1, std::string(buffer)); 
    
    // --- 2. 引用传递 ---
    int local_val = 10;
    // 使用 std::ref 显式告知需要传递引用
    std::thread t2(increment_data, std::ref(local_val));
    
    // --- 3. 成员函数传递 ---
    Worker w;
    // 传递成员函数指针和对象地址
    std::thread t3(&Worker::do_work, &w, 2);
    
    // --- 4. 移动语义传递 ---
    auto p = std::make_unique<BigData>(999);
    // std::move 将所有权转移给线程，main 函数中的 p 变为 nullptr
    std::thread t4(process_unique_ptr, std::move(p));

    // 等待所有线程结束
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    std::cout << "[Main] Final local_val is: " << local_val << " (Should be 11)" << std::endl;
    
    if (p == nullptr) {
        std::cout << "[Main] p is now null, ownership was transferred." << std::endl;
    }

    return 0;
}