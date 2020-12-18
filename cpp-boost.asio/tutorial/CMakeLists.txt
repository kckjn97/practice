cmake_minimum_required(VERSION 3.15)
project(tutorial)

set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.73.0 COMPONENTS system thread)

add_executable(timer1 timer1.cpp)
target_link_libraries(timer1 ${Boost_LIBRARIES})

add_executable(timer2 timer2.cpp)
target_link_libraries(timer2 ${Boost_LIBRARIES})

add_executable(timer3 timer3.cpp)
target_link_libraries(timer3 ${Boost_LIBRARIES})

add_executable(timer4 timer4.cpp)
target_link_libraries(timer4 ${Boost_LIBRARIES})

add_executable(timer5 timer5.cpp)
target_link_libraries(timer5 ${Boost_LIBRARIES})

add_executable(daytime1-client daytime1-client.cpp)
target_link_libraries(daytime1-client ${Boost_LIBRARIES})

add_executable(daytime2-server daytime2-server.cpp)
target_link_libraries(daytime2-server ${Boost_LIBRARIES})

add_executable(daytime3-server daytime3-server.cpp)
target_link_libraries(daytime3-server ${Boost_LIBRARIES})

add_executable(daytime4-client daytime4-client.cpp)
target_link_libraries(daytime4-client ${Boost_LIBRARIES})

add_executable(daytime5-server daytime5-server.cpp)
target_link_libraries(daytime5-server ${Boost_LIBRARIES})

add_executable(daytime6-server daytime6-server.cpp)
target_link_libraries(daytime6-server ${Boost_LIBRARIES})

add_executable(daytime7-server daytime7-server.cpp)
target_link_libraries(daytime7-server ${Boost_LIBRARIES})
