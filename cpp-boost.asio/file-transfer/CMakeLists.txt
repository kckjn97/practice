cmake_minimum_required(VERSION 3.05)
project(file_transfer)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost 1.68.0 COMPONENTS system thread)

add_executable(server server.cpp)
target_link_libraries(server ${Boost_LIBRARIES})

add_executable(client client.cpp)
target_link_libraries(client ${Boost_LIBRARIES})

