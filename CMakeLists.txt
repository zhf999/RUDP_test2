cmake_minimum_required(VERSION 3.28)
project(RUDPWebServer)

set(CMAKE_CXX_STANDARD 17)

add_executable(TCPServer TCPServer.cpp
        utils.h)
add_executable(TCPClient TCPClient.cpp utils.h)
add_executable(RUDPServer RUDPServer.cpp utils.h)
add_executable(RUDPClient RUDPClient.cpp utils.h)