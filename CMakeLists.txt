cmake_minimum_required(VERSION 3.15)
project(CPPink LANGUAGES C CXX)
set(CMAKE_BUILD_PARALLEL_LEVEL 8)

add_executable(CPPink main.cpp)
add_compile_definitions(DEBUG RPI epd7in5bV2 USE_LGPIO_LIB)

# Output the exe here, not in the build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(waveshare_libraries/config)
add_subdirectory(waveshare_libraries/ePaper)
add_subdirectory(waveshare_libraries/GUI)
add_subdirectory(waveshare_libraries/fonts)
add_subdirectory(waveshare_libraries/examples)
add_subdirectory(libraries)
add_subdirectory(utils)

target_link_libraries(CPPink PUBLIC myGUI)
target_link_libraries(CPPink PUBLIC ePaper)
target_link_libraries(CPPink PUBLIC GUI)
target_link_libraries(CPPink PUBLIC config)
target_link_libraries(CPPink PUBLIC fonts)
target_link_libraries(CPPink PUBLIC examples)