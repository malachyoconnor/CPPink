add_library(guis WeatherGUI.cpp WeatherGUI.h ../utils/BaseGUI.h)
target_include_directories(guis PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/utils
        ${CMAKE_SOURCE_DIR}/raylib
)
target_link_libraries(guis PUBLIC config ePaper fonts GUI examples bmpManager utils raylib)