cmake_minimum_required(VERSION 3.10)

# Project Name
project(TextAnalysis)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add include directory
include_directories(src/wejulu)

# Specify the binary (executable) output directory to 'bin' at the project root
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Add executable
add_executable(TextAnalysis src/wejulu/TextAnalysisAppBST.cpp src/wejulu/TextAnalysisImplBST.cpp)