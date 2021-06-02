cmake_minimum_required(VERSION 3.16)
project(sorting-efficiency VERSION 1.0.0 LANGUAGES CXX)

message(STATUS "CMake version: ${CMAKE_VERSION}")

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER "GNU")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(COMPILER "MSVC")
endif()

message(STATUS "Compiler: ${COMPILER}")

add_executable(sorting-efficiency
    src/main.cpp)

target_include_directories(sorting-efficiency PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

if (COMPILER STREQUAL "GNU")
    add_compile_options(-Wall -Wextra -Werror)
elseif (COMPILER STREQUAL "MSVC")
    add_compile_options(/Wall /WX)
else()
    message(WARNING "Unknown compiler, not setting custom compile flags")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    # The additional / is important to remove the last character from the path.
    # Note that it does not matter if the OS uses / or \, because we are only
    # saving the path size.
    # Thanks: https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)

    add_compile_definitions(DEBUG SOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})

    if (COMPILER STREQUAL "GNU")
        add_compile_options(-g3)
    elseif (COMPILER STREQUAL "MSVC")
        add_compile_options(/Z7 /Od)
    endif()
else ()
    if (COMPILER STREQUAL "GNU")
        add_compile_options(-Ofast -g0)
    elseif (COMPILER STREQUAL "MSVC")
        add_compile_options(/O2 /Oi /link /DEBUG:NONE)
    endif()
endif ()

target_compile_features(sorting-efficiency PRIVATE cxx_std_17)

set_target_properties(sorting-efficiency PROPERTIES OUTPUT_NAME "sorting")

add_subdirectory(tests)
