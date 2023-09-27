cmake_minimum_required(VERSION 3.26)

project(boomjs)

set(LLVM_DIR $ENV{BOOM_LLVM_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER $ENV{BOOM_C_COMPILER})
set(CMAKE_CXX_COMPILER $ENV{BOOM_CXX_COMPILER})
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/Value.cpp
    src/Context.cpp
    src/JSC/Context.cpp
    src/JSC/Value.cpp)

add_compile_options(-D__JSC__)
add_compile_options(-ferror-limit=1)
add_compile_options(-fno-exceptions)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)

add_library(boomjs ${BOOM_SRC_FILES})