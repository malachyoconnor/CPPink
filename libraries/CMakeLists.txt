add_library(screenController screenController.h screenController.cpp testScreenController.h testScreenController.cpp)
target_include_directories(screenController PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/utils
        ${CMAKE_SOURCE_DIR}/raylib
)
target_link_libraries(screenController PUBLIC config ePaper fonts GUI examples bmpManager utils raylib)