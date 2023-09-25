cmake_minimum_required(VERSION 3.26)

project(boom)

set(LLVM_DIR $ENV{BOOM_LLVM_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_C_COMPILER $ENV{BOOM_C_COMPILER})
set(CMAKE_CXX_COMPILER $ENV{BOOM_CXX_COMPILER})
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/App.cpp
    src/Color.cpp
    src/Brush.cpp
    src/Paint.cpp
    src/Emitter.cpp
    src/Math.cpp
    src/Menu.cpp
    src/Node.cpp
    src/Surface.cpp
    src/Image.cpp
    src/Window.cpp
    src/OpenGL/Context.cpp
    src/OpenGL/Paint.cpp
    src/OpenGL/Shaders.cpp
    src/OpenGL/Image.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_compile_options(-ferror-limit=1)
add_compile_options(-fno-exceptions)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BOOM_SRC_FILES ${BOOM_SRC_FILES}
        src/POSIX/Time.cpp
        src/POSIX/Sleep.cpp
        src/MacOS/App.mm
        src/MacOS/Input.mm
        src/MacOS/Menu.mm
        src/MacOS/Window.mm
        src/OpenGL/MacOS/Context.mm
        src/OpenGL/MacOS/Surface.mm)

    add_compile_options(-DGL_SILENCE_DEPRECATION -fobjc-arc)
endif()

add_library(boom ${BOOM_SRC_FILES})
