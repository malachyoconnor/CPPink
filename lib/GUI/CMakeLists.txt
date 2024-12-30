add_library(GUI STATIC
        GUI_BMPfile.c
        GUI_Paint.c
)

target_include_directories(GUI
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the config library so we can use config's symbols and headers.
target_link_libraries(GUI
        PUBLIC
        config
)