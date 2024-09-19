cmake_minimum_required(VERSION 3.5)

# 定义项目名称
project(hello_project)

# 添加静态库
add_library(hello_static STATIC ./src/hello.cpp)

# 添加动态库
add_library(hello_shared SHARED ./src/hello.cpp)

# 指定头文件目录
target_include_directories(hello_static PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(hello_shared PUBLIC ${PROJECT_SOURCE_DIR}/include)

# 添加可执行文件
add_executable(main ./src/main.cpp)

# 链接静态库到可执行文件
target_link_libraries(main PRIVATE hello_static)
