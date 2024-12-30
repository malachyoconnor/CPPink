cmake_minimum_required(VERSION 3.22)
project(CPPink)

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/Config)
add_subdirectory(lib/ePaper)
add_subdirectory(lib/GUI)

add_library(myTest STATIC myTest.cpp)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(myTest PRIVATE config)
target_link_libraries(myTest PRIVATE ePaper)
target_link_libraries(myTest PRIVATE GUI)

target_link_libraries(${PROJECT_NAME} myTest)




