#include <iostream>
#include <future>
#include <chrono>

// 模拟一个耗时计算的函数
int long_computation() {
    std::this_thread::sleep_for(std::chrono::seconds(3)); // 模拟耗时操作
    return 42; // 返回一个结果
}

int main() {
    // 使用 std::async 启动异步任务，并获得一个 std::future 对象
    std::future<int> result = std::async(std::launch::async, long_computation);

    // 在等待结果的同时可以做其他事情
    std::cout << "Doing other work while waiting for the result...\n";

    // 当需要结果时，调用 get() 来获取返回值
    int value = result.get(); // 这会阻塞直到任务完成
    std::cout << "2222Doing other work while waiting for the result...\n";
    std::cout << "The result is: " << value << std::endl;

    return 0;
}
