cmake_minimum_required(VERSION 3.26)

project(boomjs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/Context.cpp
    src/Class.cpp
    src/Poller.cpp
    src/Scope.cpp
    src/Value.cpp
    src/JSC/Context.cpp
    src/JSC/Scope.cpp
    src/JSC/Value.cpp)

add_compile_options(-Wall)
add_compile_options(-D__JSC__)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories(${CMAKE_SOURCE_DIR}/../../lib/JSC/include)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories(${CMAKE_SOURCE_DIR}/../../lib/JSC/include)
endif()

add_library(boomjs ${BOOM_SRC_FILES})