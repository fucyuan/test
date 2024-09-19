#include <iostream>
#include <future>
#include <thread>
#include <chrono>

// 异步任务函数
int async_task(int change_v) {
    std::this_thread::sleep_for(std::chrono::seconds(2)); // 模拟耗时操作
    return change_v + 10;  // 返回值
}

int main() {
    // 使用 std::async 异步启动任务 async_task，并返回 std::future 对象
    std::future<int> result = std::async(std::launch::async, async_task, 5);

    // 在等待任务完成时，主线程可以做其他事情
    std::cout << "Main thread is busy doing other things..." << std::endl;

    // 模拟主线程的其他工作
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 获取异步任务的结果（如果任务未完成，get() 会阻塞主线程，直到任务完成）
    std::cout << "Waiting for the result..." << std::endl;
    int value = result.get();  // 获取任务的返回值

    // 输出异步任务的结果
    std::cout << "Result from async task: " << value << std::endl;

    return 0;
}
