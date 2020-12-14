cmake_minimum_required(VERSION 3.15)
project(cpp_boost_asio)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.67 REQUIRED COMPONENTS system thread regex)
find_package(Threads)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})

add_executable(worker worker.cpp)
target_link_libraries(worker ${Boost_LIBRARIES})

add_executable(master master.cpp)
target_link_libraries(master ${Boost_LIBRARIES} ${CMAKE_THREAD_LIB_INIT})
