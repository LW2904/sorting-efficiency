cmake_minimum_required(VERSION 3.16)
project(sorting-efficiency VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "CMake version: ${CMAKE_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

#if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    set(COMPILER "GNU")
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#    set(COMPILER "MSVC")
#endif()
#
#message(STATUS "Compiler: ${COMPILER}")

add_executable(sorting-efficiency
    src/main.cpp)

target_include_directories(sorting-efficiency PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_compile_features(sorting-efficiency PRIVATE cxx_std_17)

set_target_properties(sorting-efficiency PROPERTIES OUTPUT_NAME "sorting")

add_subdirectory(tests)
