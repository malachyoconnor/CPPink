cmake_minimum_required(VERSION 3.15)
project(CPPink LANGUAGES C CXX)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

# Would like to get rid of the -DRPI
add_executable(CPPink main.cpp)
add_compile_definitions(DEBUG RPI epd7in5bV2 USE_LGPIO_LIB)

# Output the exe here, not in the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(lib/config)
add_subdirectory(lib/ePaper)
add_subdirectory(lib/GUI)
add_subdirectory(lib/fonts)
add_subdirectory(lib/examples)
add_subdirectory(myLibs)

target_link_libraries(CPPink PUBLIC myGUI)
target_link_libraries(CPPink PUBLIC ePaper)
target_link_libraries(CPPink PUBLIC GUI)
target_link_libraries(CPPink PUBLIC config)
target_link_libraries(CPPink PUBLIC fonts)
target_link_libraries(CPPink PUBLIC examples)