#include <iostream>
#include <thread>
#include <chrono>

void do_print(int& i) {
    // 等待 1 秒，确保主线程有机会去破坏栈内存
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "Value inside thread: " << i << std::endl; 
}

// 一个用来破坏栈内存的函数
void smash_stack() {
    int trash = 99999; // 这个变量很可能会覆盖掉之前的 local_state 的位置
    // 做一些操作防止被编译器优化掉
    std::cout << "Smashing stack with value: " << trash << std::endl;
}

void oops() {
    int local_state = 42;
    std::thread t(do_print, std::ref(local_state));
    t.detach();
} // local_state 销毁

int main() {
    oops();
    
    // 在子线程打印之前，我们调用另一个函数
    // 这个函数的栈帧会覆盖掉 oops 刚刚使用的栈空间
    smash_stack();

    // 等待子线程打印
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}