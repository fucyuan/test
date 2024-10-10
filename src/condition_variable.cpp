#include <iostream>
#include <thread>
#include <mutex>

template<typename Predicate>
void minimal_wait(std::unique_lock<std::mutex>& lk, Predicate pred) {
    while (!pred()) {
        lk.unlock();
        lk.lock();
    }
}

bool flag = false;
std::mutex mtx;

void wait_for_flag() {
    std::unique_lock<std::mutex> lk(mtx);
    minimal_wait(lk, [] { return flag; });
    std::cout << "Flag is true, proceeding..." << std::endl;
}

void set_flag() {
    std::cout << "-------..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1)); // 模拟一些工作
    {
 
        std::lock_guard<std::mutex> lock(mtx);
        flag = true;
    }
}

int main() {
    std::thread t1(wait_for_flag);
    std::thread t2(set_flag);

    t1.join();
    t2.join();

    return 0;
}
