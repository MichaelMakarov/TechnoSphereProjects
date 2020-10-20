cmake_minimum_required (VERSION 3.8)
project (Logger)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED True)
add_library (Logger 
            src/BaseLogger.cpp include/BaseLogger.h 
            src/FileLogger.cpp include/FileLogger.h
            src/StdoutLogger.cpp include/StdoutLogger.h
            src/StderrLogger.cpp include/StderrLogger.h)

set_property (TARGET Logger PROPERTY CXX_STANDARD 14)

add_executable (Test test/main.cpp)
target_link_libraries (Test Logger)
#set_property (TARGET Test PROPERTY CXX_STANDARD 14)