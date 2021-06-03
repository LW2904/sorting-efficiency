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
    target_compile_options(sorting-efficiency PRIVATE -Wall -Wextra -Werror)
elseif (COMPILER STREQUAL "MSVC")
    # /WX should be added here at some point
    target_compile_options(sorting-efficiency PRIVATE /Wall)
else()
    message(WARNING "Unknown compiler, not setting custom compile flags")
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    # The additional / is important to remove the last character from the path.
    # Note that it does not matter if the OS uses / or \, because we are only
    # saving the path size.
    # Thanks: https://stackoverflow.com/questions/8487986/file-macro-shows-full-path
    string(LENGTH "${CMAKE_SOURCE_DIR}/" SOURCE_PATH_SIZE)

    target_compile_definitions(sorting-efficiency PRIVATE DEBUG SOURCE_PATH_SIZE=${SOURCE_PATH_SIZE})

    if (COMPILER STREQUAL "GNU")
        target_compile_options(sorting-efficiency PRIVATE -g3)
    elseif (COMPILER STREQUAL "MSVC")
        target_compile_options(sorting-efficiency PRIVATE /Z7 /Od)
    endif()
else ()
    if (COMPILER STREQUAL "GNU")
        target_compile_options(sorting-efficiency PRIVATE -Ofast -g0)
    elseif (COMPILER STREQUAL "MSVC")
        target_compile_options(sorting-efficiency PRIVATE /O2 /DNDEBUG /Zi /Gy)
        target_link_options(sorting-efficiency PRIVATE
            /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF)
    endif()
endif ()

target_compile_features(sorting-efficiency PRIVATE cxx_std_17)

set_target_properties(sorting-efficiency PROPERTIES OUTPUT_NAME "sorting")

add_subdirectory(tests)

get_target_property(MAIN_CFLAGS sorting-efficiency COMPILE_OPTIONS)
message("-- Target compiler flags are: ${MAIN_CFLAGS}")

add_custom_command(TARGET sorting-efficiency POST_BUILD
    COMMAND echo built with the flags: ${MAIN_CFLAGS})

