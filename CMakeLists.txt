cmake_minimum_required(VERSION 3.12)
project(CPPink LANGUAGES C CXX)

# Would like to get rid of the -DRPI
add_definitions(-DDEBUG -DRPI -Depd7in5bV2 -DUSE_LGPIO_LIB)

# Output the exe here, not in the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
add_subdirectory(lib/config)
add_subdirectory(lib/ePaper)
add_subdirectory(lib/GUI)
add_subdirectory(lib/fonts)
add_subdirectory(lib/examples)

add_library(myTest STATIC myTest.cpp)
add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(myTest PRIVATE ePaper)
target_link_libraries(myTest PRIVATE GUI)
target_link_libraries(myTest PRIVATE config)
target_link_libraries(myTest PRIVATE fonts)
target_link_libraries(myTest PRIVATE examples)

target_link_libraries(${PROJECT_NAME} myTest)

