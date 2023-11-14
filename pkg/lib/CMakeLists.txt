cmake_minimum_required(VERSION 3.26)

project(boom)

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
    src/Font.cpp
    src/GraphicsView.cpp
    src/Image.cpp
    src/Input.cpp
    src/Math.cpp
    src/Menu.cpp
    src/Node.cpp
    src/OpenGL.cpp
    src/Paint.cpp
    src/Surface.cpp
    src/Utilities.cpp
    src/View.cpp
    src/Window.cpp
    src/OpenGL2/Context.cpp
    src/OpenGL2/Image.cpp
    src/OpenGL2/Paint.cpp
    src/OpenGL2/Shaders.cpp
    src/OpenGL2/Surface.cpp)

include_directories(${CMAKE_SOURCE_DIR}/include)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(BOOM_SRC_FILES ${BOOM_SRC_FILES}
        src/POSIX/File.cpp
        src/POSIX/Sleep.cpp
        src/POSIX/Time.cpp
        src/MacOS/Font.cpp
        src/MacOS/Alert.mm
        src/MacOS/App.mm
        src/MacOS/Input.mm
        src/MacOS/Menu.mm
        src/MacOS/OpenGL.mm
        src/MacOS/Window.mm)

    add_compile_options(-DGL_SILENCE_DEPRECATION -fobjc-arc)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(BOOM_SRC_FILES ${BOOM_SRC_FILES}
        src/Win32/Alert.cpp
        src/Win32/App.cpp
        src/Win32/File.cpp
        src/Win32/Font.cpp
        src/Win32/Input.cpp
        src/Win32/Menu.cpp
        src/Win32/OpenGL.cpp
        src/Win32/View.cpp
        src/Win32/Window.cpp)
elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(BOOM_SRC_FILES ${BOOM_SRC_FILES}
        src/Linux/File.cpp    
        src/Linux/GTK4/Alert.cpp
        src/Linux/GTK4/App.cpp
        src/Linux/GTK4/Input.cpp
        src/Linux/GTK4/Menu.cpp
        src/Linux/GTK4/OpenGL.cpp
        src/Linux/GTK4/View.cpp
        src/Linux/GTK4/Window.cpp)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(GTK4 REQUIRED gtk4)
    include_directories(${GTK4_INCLUDE_DIRS})
endif()

add_library(boom ${BOOM_SRC_FILES})
