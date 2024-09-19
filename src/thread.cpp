#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>

std::mutex cout_mutex;
std::mutex sync_mutex;
std::condition_variable cv;
int current_thread = 0;

void print_message(int id) {
    // 等待当前线程是正确的顺序
    std::unique_lock<std::mutex> lock(sync_mutex);
    cv.wait(lock, [id]() { return id == current_thread; });

    // 进入临界区，打印信息
    {
        std::lock_guard<std::mutex> guard(cout_mutex);
        std::cout << "Thread " << id << " is running." << std::endl;
    }

    // 更新当前运行的线程顺序
    current_thread++;
    cv.notify_all();
}

int main() {
    std::vector<std::thread> threads;

    // 创建并启动多个线程
    for (int i = 0; i < 5; ++i) {
        threads.push_back(std::thread(print_message, i));
    }

    // 使用 join() 等待所有线程完成
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
