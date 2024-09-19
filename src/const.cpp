#include <iostream>
#include <cassert>

// 使用 constexpr 定义编译期常量
constexpr int len_1 = 5;  // 编译期常量表达式
constexpr int len_2 = len_1 + 1;  // 编译期常量表达式
constexpr int len_3 = 1 + 2 + 3;  // 编译期常量表达式

// 使用 const 定义常量，可能在某些情况下不是编译期常量
int len = 5;
const int len_4 = len + 1;  // 非编译期常量表达式，因为 len 是运行时变量

int main() {
    // 编译期断言，用于在编译时验证表达式的正确性
    static_assert(len_1 == 5, "len_1 should be 5");
    static_assert(len_2 == 6, "len_2 should be 6");
    static_assert(len_3 == 6, "len_3 should be 6");

    // static_assert(len_4 == 6, "len_4 should be 6"); // 编译错误，因为 len_4 不是编译期常量

    // 运行时检查 len_4
    assert(len_4 == 6);  // 在运行时验证 len_4 是否为 6

    // 打印输出
    std::cout << "len_1: " << len_1 << std::endl;
    std::cout << "len_2: " << len_2 << std::endl;
    std::cout << "len_3: " << len_3 << std::endl;
    std::cout << "len_4 (运行时计算): " << len_4 << std::endl;

    return 0;
}
