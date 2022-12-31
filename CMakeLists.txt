cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(mod LANGUAGES CXX VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

set(MOD_DEBUG true)

add_library(mod INTERFACE)
target_include_directories(mod INTERFACE .)

if (MOD_DEBUG)
    add_subdirectory(examples)
endif()

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
