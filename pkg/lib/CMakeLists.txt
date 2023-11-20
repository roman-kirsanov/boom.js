cmake_minimum_required(VERSION 3.26)

project(boom)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_INCLUDE ${CMAKE_SOURCE_DIR}/include)

file(GLOB BOOM_SRC src/*.cpp)

if (${MSVC})
    set(BOOM_CFLAGS ${BOOM_CFLAGS} /wd4100 /wd4191 /wd4365 /wd4456 /wd4464 /wd4505 /wd4514 /wd4623 /wd4625 /wd4626 /wd4702 /wd4820 /wd4868 /wd5246 /wd4820 /wd5026 /wd5027 /wd5045 /wd4244 /wd4267 /wd5219)
else()
    set(BOOM_CFLAGS ${BOOM_CFLAGS} -Wall)
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(BOOM_CFLAGS ${BOOM_CFLAGS} -fsanitizer=address -g)
    else()
        set(BOOM_CFLAGS ${BOOM_CFLAGS} -O3)
    endif()
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    file(GLOB BOOM_SRC ${BOOM_SRC} src/Win32/*.cpp)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    file(GLOB BOOM_SRC ${BOOM_SRC} src/POSIX/*.cpp src/Linux/*.cpp src/Linux/GTK4/*.cpp)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BOOM_CFLAGS -DGL_SILENCE_DEPRECATION -fobjc-arc)
    file(GLOB BOOM_SRC ${BOOM_SRC} src/POSIX/*.cpp src/MacOS/*.cpp src/MacOS/*.mm)
endif()

include_directories(${BOOM_INCLUDE})
add_compile_options(${BOOM_CFLAGS})
add_library(boom ${BOOM_SRC})