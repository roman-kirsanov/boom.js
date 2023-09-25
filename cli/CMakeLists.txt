cmake_minimum_required(VERSION 3.26)

project(boom)

set(LLVM_DIR $ENV{BOOM_LLVM_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_C_COMPILER $ENV{BOOM_C_COMPILER})
set(CMAKE_CXX_COMPILER $ENV{BOOM_CXX_COMPILER})
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-D__JSC__)
add_compile_options(-fno-exceptions)
include_directories(${CMAKE_SOURCE_DIR}/../api/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)
include_directories(${CMAKE_SOURCE_DIR}/../js/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_libraries("-framework Cocoa")
    link_libraries("-framework OpenGL")
    link_libraries("-framework JavaScriptCore")
endif()

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    link_libraries(${CMAKE_SOURCE_DIR}/../lib/.cmake/debug/libboom.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../js/.cmake/debug/libboomjs.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../api/.cmake/debug/libboomapi.a)
elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
    link_libraries(${CMAKE_SOURCE_DIR}/../lib/.cmake/release/libboom.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../js/.cmake/release/libboomjs.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../api/.cmake/release/libboomapi.a)
endif()

add_executable(boom
    src/main.cpp)