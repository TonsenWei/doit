cmake_minimum_required(VERSION 3.5)

project(doit VERSION 1.0.0 LANGUAGES CXX)

# SET(CMAKE_PREFIX_PATH D:/software/qt5/5.12.9/mingw73_64/lib/cmake)

# SET(CMAKE_C_COMPILER "D:/software/qt5/Tools/mingw730_64/bin/gcc.exe")
# SET(CMAKE_CXX_COMPILER "D:/software/qt5/Tools/mingw730_64/bin/g++.exe")

# SET(CMAKE_BUILD_TYPE Debug CACHE STRING "set build type to debug")
# SET(CMAKE_BUILD_TYPE "Release")
# -g参数会生成调试信息，比如在main中增加了断点，使用-g时会在编译时加入这个断点信息
set(CMAKE_CXX_FLAGS "-g")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets Core Gui Charts REQUIRED)


if(ANDROID)
  add_library(doit SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    resources.qrc
    myserialwidget.cpp
    myserialwidget.h
    mychart.h
    mychart.cpp
    mydialog.h
    mydialog.cpp
  )
else()
  add_executable(doit WIN32
    main.cpp
    mainwindow.cpp
    mainwindow.h
    resources.qrc
    myserialwidget.cpp
    myserialwidget.h
    mychart.h
    mychart.cpp
    mydialog.h
    mydialog.cpp
  )
endif()

target_link_libraries(doit PRIVATE Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Charts)
