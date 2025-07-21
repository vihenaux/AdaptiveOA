cmake_minimum_required(VERSION 3.20)

project(AdaptiveOA
    VERSION 1.0
    LANGUAGES CXX
)

# Use Clang explicitly
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable strict warnings
add_compile_options(
    -O3
    -pedantic
    -Werror
    -Weverything
)

# Remove unwanted warnings
add_compile_options(
    -Wno-c++98-compat
)

# Add the executable
add_executable(adaptive_oa
    src/main.cpp
    src/solve.cpp
)

# Include your header-only source tree
#target_include_directories(adaptive_oa PRIVATE ${CMAKE_SOURCE_DIR})
