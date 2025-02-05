# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(matrix_mixer_VERSION_MAJOR 0)
set(matrix_mixer_VERSION_MINOR 1)


# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "/home/workstation/Instruo/pico/pico-sdk")

set(PICO_BOARD solderparty_rp2350_stamp_xl)

set(PICO_PLATFORM rp2350)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()


project(matrix_mixer C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

set(SYS_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/inc/sys)

set(APP_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/inc/app)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)


add_executable(matrix_mixer 
    ${SOURCES}
    )

pico_set_program_name(matrix_mixer "matrix_mixer")
pico_set_program_version(matrix_mixer "0.1")

pico_enable_stdio_uart(matrix_mixer 0)
pico_enable_stdio_usb(matrix_mixer 0)
pico_enable_stdio_rtt(matrix_mixer 1)


pico_generate_pio_header(matrix_mixer ${CMAKE_CURRENT_LIST_DIR}/src/sys/gc9a01_lcd.pio)
pico_generate_pio_header(matrix_mixer ${CMAKE_CURRENT_LIST_DIR}/src/sys/hello.pio)


# Add the standard library to the build
target_link_libraries(matrix_mixer
        pico_stdlib
        pico_rand)

# Add the standard include files to the build
target_include_directories(matrix_mixer PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
  ${SYS_INCLUDE_DIRECTORIES}
  ${APP_INCLUDE_DIRECTORIES}
  ${CMAKE_CURRENT_SOURCE_DIR}/inc/sys/SEGGER
  )

# Add any user requested libraries
target_link_libraries(matrix_mixer

        )

target_compile_definitions(matrix_mixer PUBLIC
  PICO_PLATFORM=rp2350
  LOG_LEVEL=DEBUG_LEVEL
  HARDWARE_VERSION=1
  )

target_link_options(matrix_mixer PRIVATE
  -Wl,--print-memory-usage)

pico_add_extra_outputs(matrix_mixer)

add_custom_command(
  TARGET matrix_mixer
  COMMAND ceedling --project ${CMAKE_CURRENT_SOURCE_DIR}/project.yml test:all
)

