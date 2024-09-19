#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
bool ready = false;

void wait_for_signal() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [] { return ready; });  // 使用 unique_lock 和 lambda 作为条件
    std::cout << "Thread is awake!" << std::endl;
}

void send_signal() {
    std::lock_guard<std::mutex> lock(mtx);
    std::cout << "Thread is no  awake!" << std::endl;
    ready = true;  // 修改共享数据
    cv.notify_one();  // 唤醒等待的线程
}

int main() {
    std::thread t1(wait_for_signal);
    std::thread t2(send_signal);

    t1.join();
    t2.join();
    return 0;
}
