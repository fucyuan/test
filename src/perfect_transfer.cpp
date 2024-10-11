#include <iostream>
#include <utility>

// 一个简单的函数，用来测试完美转发
void process(int& x) {
    std::cout << "Lvalue reference process: " << x << std::endl;
}

void process(int&& x) {
    std::cout << "Rvalue reference process: " << x << std::endl;
}

// 包装函数，使用完美转发
template <typename T>
void wrapper(T&& arg) {
    process(std::forward<T>(arg)); // 完美转发参数 arg 到 process 函数
}

int main() {
    int a = 5;
    wrapper(a);        // 调用左值引用版本的 process
    wrapper(10);       // 调用右值引用版本的 process

    return 0;
}
