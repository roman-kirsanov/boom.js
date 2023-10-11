cmake_minimum_required(VERSION 3.26)

project(boom)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
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

execute_process(
    COMMAND pnpm i
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
execute_process(
    COMMAND npx esbuild ${CMAKE_SOURCE_DIR}/src/main.ts --bundle --platform=neutral --format=iife --outfile=${CMAKE_BINARY_DIR}/cli.js
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

file(READ ${CMAKE_SOURCE_DIR}/src/compat.js COMPAT HEX)
file(READ ${CMAKE_BINARY_DIR}/cli.js BOOM_CLI HEX)
string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," COMPAT "${COMPAT}")
string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," BOOM_CLI "${BOOM_CLI}")
file(WRITE ${CMAKE_BINARY_DIR}/embed.cpp "static char const __COMPAT[] = {${COMPAT}0x00};\n")
file(APPEND ${CMAKE_BINARY_DIR}/embed.cpp "static char const __BOOM_CLI[] = {${BOOM_CLI}0x00};\n")
file(APPEND ${CMAKE_BINARY_DIR}/embed.cpp "extern \"C\" char const* COMPAT() { return __COMPAT; }\n")
file(APPEND ${CMAKE_BINARY_DIR}/embed.cpp "extern \"C\" char const* BOOM_CLI() { return __BOOM_CLI; }\n")

add_executable(boom
    src/main.cpp
    ${CMAKE_BINARY_DIR}/embed.cpp)