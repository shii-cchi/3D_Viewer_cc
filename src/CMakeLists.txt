cmake_minimum_required(VERSION 3.1.0)

project(3D_Viewer VERSION 1.0.0 LANGUAGES CXX)

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
    viewer_controller/viewer_controller.cc
    viewer_controller/viewer_controller.h
    viewer_model/parser.cc
    viewer_model/parser.h
    viewer_model/transform.cc
    viewer_model/transform.h
    viewer_model/viewer_model.cc
    viewer_model/viewer_model.h

    QtGifImage/gifimage/qgifglobal.h
    QtGifImage/gifimage/qgifimage.cpp
    QtGifImage/gifimage/qgifimage.h
    QtGifImage/gifimage/qgifimage_p.h
    QtGifImage/giflib/dgif_lib.c
    QtGifImage/giflib/egif_lib.c
    QtGifImage/giflib/gif_err.c
    QtGifImage/giflib/gif_font.c
    QtGifImage/giflib/gif_hash.c
    QtGifImage/giflib/gif_hash.h
    QtGifImage/giflib/gif_lib.h
    QtGifImage/giflib/gif_lib_private.h
    QtGifImage/giflib/gifalloc.c
    QtGifImage/giflib/quantize.c
)

target_link_libraries(3D_Viewer Qt6::Widgets Qt6::Core)
target_link_libraries(3D_Viewer Qt6::Charts Qt6::Core)
