#include <thread>
#include <iostream>
#include <stdexcept>

class scoped_thread {
    std::thread t;
public:
    explicit scoped_thread(std::thread t_): t(std::move(t_)) {
        if (!t.joinable()) throw std::logic_error("No thread");
    }
    ~scoped_thread() { t.join(); }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
};

struct func {
    void operator()(int& i) { ++i; }
};

void do_something_in_current_thread() {
    std::cout << "Main thread working...\n";
}

int main() {
    int some_local_state = 0;
    scoped_thread t(std::thread(func(), std::ref(some_local_state)));
    do_something_in_current_thread();
    return 0;
}
