# At the moment we're only including the header
add_library(config STATIC Debug.h DEV_Config.c dev_hardware_SPI.c RPI_gpiod.c)

find_library(LGPIO_LIB lgpio)
target_link_libraries(config ${LGPIO_LIB})

target_include_directories(config PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)