cmake_minimum_required(VERSION 3.20)

set(CMAKE_TOOLCHAIN_FILE lib/cmake-arm-embedded/toolchain-arm-none-eabi.cmake)

project(ltboot C ASM)

set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")

include(cmake/GitVersion.cmake)
include(lib/cmake-arm-embedded/binutils-arm-none-eabi.cmake)

add_subdirectory(lib)
add_subdirectory(src)
