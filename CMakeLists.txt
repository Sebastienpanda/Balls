# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.0)
set(toolchainVersion RISCV_RPI_2_0_0_5)
set(picotoolVersion 2.1.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico2_w CACHE STRING "Board type")
set(PIMORONI_PICO_PATH ${USERHOME}/.pico-sdk/3rdparty/pimoroni-pico/)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)
include(${USERHOME}/.pico-sdk/3rdparty/pimoroni-pico/pimoroni_pico_import.cmake)

project(Balls C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Balls Balls.cc )
include(common/pimoroni_i2c)
include(common/pimoroni_bus)
include(libraries/pico_display_2/pico_display_2)
include(libraries/pico_graphics/pico_graphics)
include(drivers/st7789/st7789)
include(drivers/rgbled/rgbled)
include(drivers/button/button)


pico_set_program_name(Balls "Balls")
pico_set_program_version(Balls "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Balls 0)
pico_enable_stdio_usb(Balls 0)

# Add the standard library to the build
target_link_libraries(Balls
        pico_stdlib
        # pico_cyw43_arch_none
        hardware_spi
        hardware_pwm
        hardware_dma
        rgbled
        button
        pico_display_2
        st7789
        pico_graphics
)

# Add the standard include files to the build
target_include_directories(Balls PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(Balls)

