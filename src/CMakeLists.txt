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
    view/main.cc
    view/mainwindow.cc
    view/mainwindow.h
    view/mainwindow.ui
    view/glview.cc
    view/glview.h
    viewer_contoller/viewer_contoller.cc
    viewer_contoller/viewer_contoller.h
    viewer_model/parcer.cc
    viewer_model/parcer.h 
    viewer_model/transform.cc
    viewer_model/transform.h
    viewer_model/viewer_model.cc
    viewer_model/viewer_model.h
)

target_link_libraries(3D_Viewer Qt6::Widgets Qt6::Core)
target_link_libraries(3D_Viewer Qt6::Charts Qt6::Core)