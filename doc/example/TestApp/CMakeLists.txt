cmake_minimum_required(VERSION 3.26)

project(TestApp)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

include_directories(${CMAKE_SOURCE_DIR}/../../../pkg/lib/include)
add_compile_options(-g -Wall)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    link_libraries("-framework Cocoa")
    link_libraries("-framework OpenGL")
    link_libraries(${CMAKE_SOURCE_DIR}/../../../pkg/lib/.build/${CMAKE_BUILD_TYPE}/libboom.a)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # TODO: Fix this bs...
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(MSBUILD_TARGET_OUTPUT Debug/Debug)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        set(MSBUILD_TARGET_OUTPUT Release/Release)
    endif()

    link_libraries(opengl32.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../../../pkg/lib/.build/${MSBUILD_TARGET_OUTPUT}/boom.lib)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    add_compile_options(-fsanitize=address)
    add_link_options(-fsanitize=address)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    link_libraries(${CMAKE_SOURCE_DIR}/../../../pkg/lib/.build/${CMAKE_BUILD_TYPE}/libboom.a)
    link_libraries(${GTK4_LIBRARIES})
    link_libraries(GL)
endif()

add_executable(TestApp
    src/Header/Header.cpp
    src/Content/Content.cpp
    src/Sidebar/Sidebar.cpp
    src/main.cpp)