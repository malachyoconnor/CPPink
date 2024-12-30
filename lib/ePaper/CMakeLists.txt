add_library(ePaper STATIC
        EPD_7in5_V2.c
)

target_include_directories(ePaper
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link the config library so we can use config's symbols and headers.
target_link_libraries(ePaper
        PUBLIC
        config
)
