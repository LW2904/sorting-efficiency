cmake_minimum_required(VERSION 3.16)
project(sorting-efficiency VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "CMake version: ${CMAKE_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

add_executable(sorting-efficiency
    src/main.cpp)

target_include_directories(sorting-efficiency PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_compile_options(-Wall -Wextra -Werror)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    # The additional / is important to remove the last character from the path.
    # Note that it does not matter if the OS uses / or \, because we are only
    # saving the path size.
    # Thanks: https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)

    add_compile_definitions(DEBUG SOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})
    add_compile_options(-g3)
else ()
    add_compile_options(-Ofast -g0)
endif ()

target_compile_features(sorting-efficiency PRIVATE cxx_std_17)

set_target_properties(sorting-efficiency PROPERTIES OUTPUT_NAME "sorting")

add_subdirectory(tests)
