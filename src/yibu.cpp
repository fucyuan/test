#include <iostream>
#include <future>
#include <thread>
#include <chrono>
#include <mutex>

std::mutex cout_mutex;  // 保护 std::cout 的互斥锁

int download_file(const std::string& file_url) {
    {
        // 使用互斥锁保护输出操作
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Downloading from " << file_url << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));  // 模拟下载时间

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Download from " << file_url << " complete." << std::endl;
    }

    return 10;  // 假设下载文件大小为 10MB
}

void process_file(int file_size) {
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Processing file of size " << file_size << "MB..." << std::endl;
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));  // 模拟计算时间

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "File processing complete." << std::endl;
    }
}

int main() {
    std::string file_url1 = "http://example.com/file1";
    std::string file_url2 = "http://example.com/file2";

    // 异步启动两个下载任务
    std::future<int> file1 = std::async(std::launch::async, download_file, file_url1);
    std::future<int> file2 = std::async(std::launch::async, download_file, file_url2);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Main thread is free to do other work while downloading..." << std::endl;
    }

    // 主线程可以做其他工作，这里模拟休眠
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 获取异步下载的结果
    int file_size1 = file1.get();
    int file_size2 = file2.get();

    // 开始处理下载完成的文件
    process_file(file_size1);
    process_file(file_size2);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "All tasks completed." << std::endl;
    }

    return 0;
}
