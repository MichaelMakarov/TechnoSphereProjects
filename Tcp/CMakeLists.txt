cmake_minimum_required (VERSION 3.8)
project (Tcp)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)
include_directories(include)
add_library (Tcp src/Connection.cpp 
                 src/TcpConnection.cpp
                 src/ConnectionUtils.cpp 
                 src/Client.cpp
                 src/Server.cpp)
