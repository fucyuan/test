#include <iostream>
#include <thread>
#include <mutex>

std::mutex m1;
std::mutex m2;

void task1() {
    // 线程1首先锁定 m1，然后尝试锁定 m2
    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 模拟一些处理延迟
    std::lock_guard<std::mutex> lock2(m2);  // 尝试锁定 m2
    std::cout << "Task 1: Acquired both locks" << std::endl;
}

void task2() {
    // 线程2首先锁定 m2，然后尝试锁定 m1
    std::lock_guard<std::mutex> lock1(m1);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));  // 模拟一些处理延迟
    std::lock_guard<std::mutex> lock2(m2);  // 尝试锁定 m1
    std::cout << "Task 2: Acquired both locks" << std::endl;
}

int main() {
    std::thread t1(task1);
    std::thread t2(task2);

    t1.join();
    t2.join();

    return 0;
}
