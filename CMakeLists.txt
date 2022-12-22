cmake_minimum_required(VERSION 3.0.0)
project(PixelEngine VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(PixelEngine main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Set the output directory for the build executables into the bin/ARM64 folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/ARM64)

# Include standard c++ libraries
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
