cmake_minimum_required(VERSION 3.10)
project(TcpServer)

set(CMAKE_CXX_STANDARD 17)

# Указываем путь к библиотекам и заголовкам libev
include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(server server.cpp)
target_link_libraries(server ev)
