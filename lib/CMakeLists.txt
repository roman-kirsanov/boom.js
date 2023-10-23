cmake_minimum_required(VERSION 3.26)

project(boom)

include(FetchContent)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)
set(BOOM_SRC_FILES
    src/Alert.cpp
    src/App.cpp
    src/Brush.cpp
    src/Buffer.cpp
    src/Color.cpp
    src/Emitter.cpp
    src/Error.cpp
    src/File.cpp
    src/Image.cpp
    src/Math.cpp
    src/Menu.cpp
    src/Node.cpp
    src/Paint.cpp
    src/Surface.cpp
    src/Utilities.cpp
    src/Window.cpp
    src/OpenGL/Context.cpp
    src/OpenGL/Image.cpp
    src/OpenGL/Paint.cpp
    src/OpenGL/Shaders.cpp)

add_compile_options(-ferror-limit=1)
include_directories(${CMAKE_SOURCE_DIR}/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BOOM_SRC_FILES ${BOOM_SRC_FILES}
        src/POSIX/Time.cpp
        src/POSIX/Sleep.cpp
        src/POSIX/File.cpp
        src/MacOS/App.mm
        src/MacOS/Input.mm
        src/MacOS/Menu.mm
        src/MacOS/Window.mm
        src/MacOS/Alert.mm
        src/OpenGL/MacOS/Context.mm
        src/OpenGL/MacOS/Surface.mm)

    add_compile_options(-DGL_SILENCE_DEPRECATION -fobjc-arc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    FetchContent_Declare(glew URL https://sourceforge.net/projects/glew/files/glew/2.2.0/glew-2.2.0.zip)
    FetchContent_MakeAvailable(glew)

    include_directories(${glew_SOURCE_DIR}/include)
endif()

add_library(boom ${BOOM_SRC_FILES})
