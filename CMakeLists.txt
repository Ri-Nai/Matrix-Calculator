cmake_minimum_required(VERSION 3.10)
project(Matrix_Calculator)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)
add_definitions("-fexec-charset=GBK")

# 包含头文件目录
include_directories(include)

# 添加可执行文件
aux_source_directory(./src SRC_LIST)
add_executable(Matrix_Calculator ${SRC_LIST})

# 链接FTXUI库
