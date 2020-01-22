cmake_minimum_required(VERSION 3.15)
project(RakNetP2PTest)
set(CMAKE_CXX_STANDARD 14)

add_executable(RakNetP2PClient Client_main.cpp Common.h)
target_link_libraries(RakNetP2PClient raknet pthread)

add_executable(RakNetP2PServer Server_main.cpp)
target_link_libraries(RakNetP2PServer raknet pthread)