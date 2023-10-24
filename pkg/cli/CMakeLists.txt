cmake_minimum_required(VERSION 3.26)

project(boom)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_compile_options(-D__JSC__)
include_directories(${CMAKE_SOURCE_DIR}/../api/include)
include_directories(${CMAKE_SOURCE_DIR}/../lib/include)
include_directories(${CMAKE_SOURCE_DIR}/../js/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    # TODO: Fix this bs...
    if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
        set(MSBUILD_TARGET_OUTPUT Debug/Debug)
    elseif(${CMAKE_BUILD_TYPE} MATCHES "Release")
        set(MSBUILD_TARGET_OUTPUT Release/Release)
    endif()

    link_libraries(opengl32.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../../lib/glew/lib/win32/x86_64/glew32s.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/JavaScriptCore.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/${MSBUILD_TARGET_OUTPUT}/boom.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/${MSBUILD_TARGET_OUTPUT}/boomjs.lib)
    link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/${MSBUILD_TARGET_OUTPUT}/boomapi.lib)

    file(COPY ${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/JavaScriptCore.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file(COPY ${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/WTF.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file(COPY ${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/icudt73.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file(COPY ${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/icuin73.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
    file(COPY ${CMAKE_SOURCE_DIR}/../../lib/JSC/lib/win32/x86_64/icuuc73.dll DESTINATION ${CMAKE_BINARY_DIR}/${CMAKE_BUILD_TYPE})
else()
    link_libraries(${CMAKE_SOURCE_DIR}/../lib/.build/${CMAKE_BUILD_TYPE}/libboom.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../js/.build/${CMAKE_BUILD_TYPE}/libboomjs.a)
    link_libraries(${CMAKE_SOURCE_DIR}/../api/.build/${CMAKE_BUILD_TYPE}/libboomapi.a)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    link_libraries("-framework Cocoa")
    link_libraries("-framework OpenGL")
    link_libraries("-framework JavaScriptCore")
endif()

add_executable(boom
    src/main.cpp
    ${CMAKE_BINARY_DIR}/embed.cpp)