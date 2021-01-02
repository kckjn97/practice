cmake_minimum_required(VERSION 3.11)
project(file_transfer)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.73.0 COMPONENTS system thread)

add_executable(server server.cpp)
target_link_libraries(server ${Boost_LIBRARIES})

add_executable(sender sender.cpp)
target_link_libraries(sender ${Boost_LIBRARIES})

add_executable(receiver receiver.cpp)
target_link_libraries(receiver ${Boost_LIBRARIES})
