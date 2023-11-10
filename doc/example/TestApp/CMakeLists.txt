cmake_minimum_required(VERSION 3.26)

project(TestApp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/../../../pkg/lib/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # TODO: Fix this bs...
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(MSBUILD_TARGET_OUTPUT Debug/Debug)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        set(MSBUILD_TARGET_OUTPUT Release/Release)
    endif()

    link_libraries(opengl32.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../../../pkg/lib/.build/${MSBUILD_TARGET_OUTPUT}/boom.lib)
else()
    link_libraries(${CMAKE_SOURCE_DIR}/../../../pkg/lib/.build/${CMAKE_BUILD_TYPE}/libboom.a)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_libraries("-framework Cocoa")
    link_libraries("-framework OpenGL")
endif()

add_executable(TestApp
    src/Content/Content.cpp
    src/Header/Header.cpp
    src/Sidebar/Sidebar.cpp
    src/main.cpp)