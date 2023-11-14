cmake_minimum_required(VERSION 3.26)

project(boomapi)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/App.cpp
    src/Console.cpp
    src/File.cpp
    src/Input.cpp
    src/Math.cpp
    src/Process.cpp
    src/Window.cpp)
set(BOOM_DTS_FILES
    src/App.d.ts
    src/Console.d.ts
    src/File.d.ts
    src/Input.d.ts
    src/Math.d.ts
    src/Process.d.ts
    src/Utilities.d.ts
    src/Window.d.ts)

add_compile_options(-Wall)
add_compile_options(-D__JSC__)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/../js/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)
include_directories(${CMAKE_SOURCE_DIR}/../api/include)

if (${MSVC})
    add_compile_options(/wd4100 /wd4191 /wd4365 /wd4456 /wd4464 /wd4505 /wd4514 /wd4623 /wd4625 /wd4626 /wd4702 /wd4820 /wd4868 /wd5246 /wd4820 /wd5026 /wd5027 /wd5045 /wd4244 /wd4267 /wd5219)
else()
    # TODO: ...
endif()

add_library(boomapi ${BOOM_SRC_FILES})

file(REMOVE ${CMAKE_BINARY_DIR}/boom.d.ts)
foreach(INPUT ${BOOM_DTS_FILES})
    file(READ ${INPUT} CONTENTS)
    file(APPEND ${CMAKE_BINARY_DIR}/boom.d.ts ${CONTENTS} \n\n)
endforeach()