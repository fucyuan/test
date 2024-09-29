#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <stdexcept>

class Account {
public:
    int balance;
    std::mutex m;  // 每个账户都有一个互斥量来保护余额操作

    Account(int balance_) : balance(balance_) {}

    // 显示账户余额
    void show_balance() {
        std::cout << "Balance: " << balance << std::endl;
    }
};

// 安全转账函数，将一定数量的钱从 lhs 账户转到 rhs 账户
void transfer(Account& lhs, Account& rhs, int amount) {
    if (&lhs == &rhs) {
        std::cout << "Cannot transfer to the same account." << std::endl;
        return;  // 自我转账没有意义
    }

    // 使用 std::lock 来锁定两个账户的互斥量，防止死锁
    std::lock(lhs.m, rhs.m);

    // std::adopt_lock 用于通知 lock_guard，互斥量已经被锁定
    std::lock_guard<std::mutex> lock_lhs(lhs.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock_rhs(rhs.m, std::adopt_lock);

    // 模拟一些转账操作
    if (lhs.balance >= amount) {
        lhs.balance -= amount;
        rhs.balance += amount;
        std::cout << "Transferred " << amount << " from Account A to Account B." << std::endl;
    } else {
        std::cout << "Insufficient funds to transfer from Account A to Account B." << std::endl;
    }
}
