cmake_minimum_required(VERSION 3.26)

project(boomapi)

set(LLVM_DIR $ENV{BOOM_LLVM_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_C_COMPILER $ENV{BOOM_C_COMPILER})
set(CMAKE_CXX_COMPILER $ENV{BOOM_CXX_COMPILER})
set(CMAKE_CXX_STANDARD 23)

set(BOOM_SRC_FILES
    src/Math.cpp
    src/Input.cpp
    src/App.cpp
    src/Window.cpp
    src/Console.cpp
    src/Process.cpp)

set(BOOM_DTS_FILES
    src/App.d.ts
    src/Math.d.ts
    src/Input.d.ts
    src/Window.d.ts
    src/Console.d.ts
    src/Process.d.ts
    src/Utilities.d.ts)

add_compile_options(-D__JSC__)
add_compile_options(-ferror-limit=1)
add_compile_options(-fno-exceptions)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../js/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)
include_directories(${CMAKE_SOURCE_DIR}/../api/include)

add_library(boomapi ${BOOM_SRC_FILES})

file(REMOVE ${CMAKE_BINARY_DIR}/boom.d.ts)
foreach(INPUT ${BOOM_DTS_FILES})
    file(READ ${INPUT} CONTENTS)
    file(APPEND ${CMAKE_BINARY_DIR}/boom.d.ts ${CONTENTS} \n\n)
endforeach()