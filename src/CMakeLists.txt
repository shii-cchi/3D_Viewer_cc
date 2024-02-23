cmake_minimum_required(VERSION 3.1.0)

project(3D_Viewer VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
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

    view/QtGifImage/gifimage/qgifglobal.h
    view/QtGifImage/gifimage/qgifimage.cpp
    view/QtGifImage/gifimage/qgifimage.h
    view/QtGifImage/gifimage/qgifimage_p.h
    view/QtGifImage/giflib/dgif_lib.c
    view/QtGifImage/giflib/egif_lib.c
    view/QtGifImage/giflib/gif_err.c
    view/QtGifImage/giflib/gif_font.c
    view/QtGifImage/giflib/gif_hash.c
    view/QtGifImage/giflib/gif_hash.h
    view/QtGifImage/giflib/gif_lib.h
    view/QtGifImage/giflib/gif_lib_private.h
    view/QtGifImage/giflib/gifalloc.c
    view/QtGifImage/giflib/quantize.c
)

target_link_libraries(3D_Viewer Qt6::Widgets Qt6::Core)
target_link_libraries(3D_Viewer Qt6::Charts Qt6::Core)
