
cmake_minimum_required(VERSION 3.10)

project(any LANGUAGES CXX)

add_executable(any src/main.cpp
                   src/Any.hpp)

set(default_build_type "Debug")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message("Message: Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(any PRIVATE $<$<CONFIG:RELEASE>:-O2>)
    target_compile_options(any PRIVATE $<$<CONFIG:DEBUG>:-Wall;-Wextra;-Wpedantic>)
endif()

set_target_properties(any PROPERTIES CXX_STANDARD 17
                                     CXX_STANDARD_REQUIRED on)