cmake_minimum_required(VERSION 3.26)

project(boomjs)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/Context.cpp
    src/Poller.cpp
    src/Scope.cpp
    src/Value.cpp
    src/JSC/Context.cpp
    src/JSC/Scope.cpp
    src/JSC/Value.cpp)

add_compile_options(-D__JSC__)
add_compile_options(-ferror-limit=1)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FetchContent_Declare(webkit GIT_REPOSITORY https://github.com/WebKit/WebKit.git GIT_TAG main)
    FetchContent_MakeAvailable(webkit)

    include_directories(${webkit_SOURCE_DIR}/include)
endif()

add_library(boomjs ${BOOM_SRC_FILES})