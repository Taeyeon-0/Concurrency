#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <vector>

void edit_document(std::string filename) {
    std::cout << "[Thread " << std::this_thread::get_id() << "] Opening document: " << filename << std::endl;
    
    // 模拟文档编辑过程
    for (int i = 0; i < 3; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::cout << "[Thread " << std::this_thread::get_id() << "] Autosaving " << filename << "..." << std::endl;
    }
    
    std::cout << "[Thread " << std::this_thread::get_id() << "] Finished editing " << filename << std::endl;
}

int main() {
    std::cout << "[Main] Application started.\n";

    // 模拟用户打开多个文档
    std::vector<std::string> docs = {"resume.doc", "budget.xls", "notes.txt"};

    for (const auto& doc : docs) {
        // 启动新线程处理文档，并传入文件名参数
        std::thread t(edit_document, doc);
        
        // 分离线程，让其在后台独立运行
        t.detach();
    }

    std::cout << "[Main] All documents opened. Main thread continues...\n";

    // 暂停主线程，防止主程序退出导致后台线程被强制关闭
    std::this_thread::sleep_for(std::chrono::seconds(3));
    
    std::cout << "[Main] Application exiting.\n";
    return 0;
}