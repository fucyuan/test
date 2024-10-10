#include <iostream>
#include <thread>
#include <semaphore.h>
#include <chrono>

sem_t sem; // 定义一个 POSIX 信号量

void thread_func() {
    std::cout << "Thread waiting for signal...\n";
    sem_wait(&sem); // 等待信号量
    std::cout << "Thread received signal!\n";
}

int main() {
    // 初始化信号量，0 表示该信号量在线程间共享，初始值为0
    sem_init(&sem, 0, 0);

    std::thread t1(thread_func);
    std::thread t2(thread_func);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    sem_post(&sem); // 释放信号量，唤醒一个线程
    sem_post(&sem); // 再次释放信号量，唤醒另一个线程

    t1.join();
    t2.join();

    sem_destroy(&sem); // 销毁信号量
    return 0;
}
