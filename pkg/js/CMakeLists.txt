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

if (${MSVC})
    add_compile_options(/wd4100 /wd4191 /wd4365 /wd4456 /wd4464 /wd4505 /wd4514 /wd4623 /wd4625 /wd4626 /wd4702 /wd4820 /wd4868 /wd5246 /wd4820 /wd5026 /wd5027 /wd5045 /wd4244 /wd4267 /wd5219)
else()
    # TODO: ...
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    include_directories(${CMAKE_SOURCE_DIR}/../../lib/JSC/include)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    include_directories(${CMAKE_SOURCE_DIR}/../../lib/JSC/include)
endif()

add_library(boomjs ${BOOM_SRC_FILES})