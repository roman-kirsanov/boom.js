cmake_minimum_required(VERSION 3.26)

project(boomjs)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_CFLAGS -D__JSC__)
set(BOOM_INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(BOOM_INCLUDE ${BOOM_INCLUDE} ${CMAKE_SOURCE_DIR}/../lib/include)
set(BOOM_INCLUDE ${BOOM_INCLUDE} ${CMAKE_SOURCE_DIR}/../../lib/JSC/include)

file(GLOB BOOM_SRC src/*.cpp src/JSC/*.cpp)

if (${MSVC})
    set(BOOM_CFLAGS ${BOOM_CFLAGS} /Zi /wd4100 /wd4191 /wd4365 /wd4456 /wd4464 /wd4505 /wd4514 /wd4623 /wd4625 /wd4626 /wd4702 /wd4820 /wd4868 /wd5246 /wd4820 /wd5026 /wd5027 /wd5045 /wd4244 /wd4267 /wd5219)
else()
    set(BOOM_CFLAGS ${BOOM_CFLAGS} -Wall)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(BOOM_CFLAGS ${BOOM_CFLAGS} -fsanitizer=address -g)
    else()
        set(BOOM_CFLAGS ${BOOM_CFLAGS} -O3)
    endif()
endif()

include_directories(${BOOM_INCLUDE})
add_compile_options(${BOOM_CFLAGS})
add_library(boomjs ${BOOM_SRC})