#include <iostream>
#include <thread>

// 1. 普通函数
void hello_function() {
    std::cout << "[Function] Hello from function pointer!" << std::endl;
}

// 2. 函数对象
class HelloFunctor {
public:
    void operator()() const {
        std::cout << "[Functor] Hello from functor!" << std::endl;
    }
};

int main() {
    // 启动方式 1: 函数指针
    std::thread t1(hello_function);

    // 启动方式 2: 函数对象 (使用统一初始化语法避免解析歧义)
    std::thread t2{ HelloFunctor() };

    // 启动方式 3: Lambda 表达式
    std::thread t3([] {
        std::cout << "[Lambda] Hello from lambda!" << std::endl;
    });

    // 等待所有线程结束
    t1.join();
    t2.join();
    t3.join();

    return 0;
}