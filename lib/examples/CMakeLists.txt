add_library(examples STATIC EPD_7in5_V2_test.c EPD_7in5_V2_test_old.c ImageData.c EPD_Test.h)

target_include_directories(examples
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(examples
        PUBLIC
        ePaper
        GUI
        config
        fonts
)