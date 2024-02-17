cmake_minimum_required(VERSION 3.1.0)

project(3D_Viewer VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Charts REQUIRED)

add_executable(3D_Viewer
    view/main.cpp
    view/mainwindow.cpp
    view/mainwindow.h
    view/mainwindow.ui
    view/glview.cpp
    view/glview.h
    core/parser.c
    core/parser.h
    core/structs.h
    core/transform.c
    core/transform.h
)

target_link_libraries(3D_Viewer Qt6::Widgets Qt6::Core)
target_link_libraries(3D_Viewer Qt6::Charts Qt6::Core)