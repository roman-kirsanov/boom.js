cmake_minimum_required(VERSION 3.26)

project(boom)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-D__JSC__)
include_directories(${CMAKE_SOURCE_DIR}/../api/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)
include_directories(${CMAKE_SOURCE_DIR}/../js/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    link_libraries(${CMAKE_SOURCE_DIR}/../../lib/glew/lib/win32/x86_64/glew32s.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/JavaScriptCore.lib)

    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/debug/Debug/boom.lib)
        link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/debug/Debug/boomjs.lib)
        link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/debug/Debug/boomapi.lib)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/release/Release/boom.lib)
        link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/release/Release/boomjs.lib)
        link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/release/Release/boomapi.lib)
    endif()
else()
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/debug/libboom.a)
        link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/debug/libboomjs.a)
        link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/debug/libboomapi.a)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/release/libboom.a)
        link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/release/libboomjs.a)
        link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/release/libboomapi.a)
    endif()
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_libraries("-framework Cocoa")
    link_libraries("-framework OpenGL")
    link_libraries("-framework JavaScriptCore")
endif()

add_executable(boom
    src/main.cpp
    ${CMAKE_BINARY_DIR}/embed.cpp)