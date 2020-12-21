cmake_minimum_required(VERSION 3.15)
project(cpp_boost_asio)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.73 REQUIRED COMPONENTS system thread)
find_package(Threads)

add_executable(worker worker.cpp)
target_link_libraries(worker ${Boost_LIBRARIES})

add_executable(master master.cpp)
target_link_libraries(master ${Boost_LIBRARIES})
