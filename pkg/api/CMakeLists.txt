cmake_minimum_required(VERSION 3.26)

project(boomapi)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_FLAGS -D__JSC__)
set(BOOM_INCLUDE ${CMAKE_SOURCE_DIR}/include)
set(BOOM_INCLUDE ${BOOM_INCLUDE} ${CMAKE_SOURCE_DIR}/../js/include)
set(BOOM_INCLUDE ${BOOM_INCLUDE} ${CMAKE_SOURCE_DIR}/../lib/include)

file(GLOB BOOM_SRC src/*.cpp)
file(GLOB BOOM_DTS src/*.d.ts)

if (${MSVC})
    set(BOOM_FLAGS ${BOOM_FLAGS} /wd4100 /wd4191 /wd4365 /wd4456 /wd4464 /wd4505 /wd4514 /wd4623 /wd4625 /wd4626 /wd4702 /wd4820 /wd4868 /wd5246 /wd4820 /wd5026 /wd5027 /wd5045 /wd4244 /wd4267 /wd5219)
else()
    set(BOOM_FLAGS ${BOOM_FLAGS} -Wall)
endif()

file(REMOVE ${CMAKE_BINARY_DIR}/boom.d.ts)
foreach(INPUT ${BOOM_DTS_FILES})
    file(READ ${INPUT} CONTENTS)
    file(APPEND ${CMAKE_BINARY_DIR}/boom.d.ts ${CONTENTS} \n\n)
endforeach()

include_directories(${BOOM_INCLUDE})
add_compile_options(${BOOM_FLAGS})
add_library(boomapi ${BOOM_SRC})