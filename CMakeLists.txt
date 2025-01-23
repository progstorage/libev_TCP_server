cmake_minimum_required(VERSION 3.10)
project(TcpServer)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBEV REQUIRED ev)

include_directories(${LIBEV_INCLUDE_DIRS})
link_directories(${LIBEV_LIBRARY_DIRS})

add_executable(server server.cpp)
target_link_libraries(server ${LIBEV_LIBRARIES})
