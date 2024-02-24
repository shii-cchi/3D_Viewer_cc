cmake_minimum_required(VERSION 3.1.0)

project(3D_Viewer VERSION 2.0.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(Qt6 COMPONENTS Charts REQUIRED)

add_executable(3D_Viewer
    viewer_view/main.cc
    viewer_view/mainwindow.cc
    viewer_view/mainwindow.h
    viewer_view/mainwindow.ui
    viewer_view/glview.cc
    viewer_view/glview.h
    viewer_controller/viewer_controller.cc
    viewer_controller/viewer_controller.h
    viewer_model/parser.cc
    viewer_model/parser.h
    viewer_model/transform.cc
    viewer_model/transform.h
    viewer_model/viewer_model.cc
    viewer_model/viewer_model.h

    viewer_view/QtGifImage/gifimage/qgifglobal.h
    viewer_view/QtGifImage/gifimage/qgifimage.cpp
    viewer_view/QtGifImage/gifimage/qgifimage.h
    viewer_view/QtGifImage/gifimage/qgifimage_p.h
    viewer_view/QtGifImage/giflib/dgif_lib.c
    viewer_view/QtGifImage/giflib/egif_lib.c
    viewer_view/QtGifImage/giflib/gif_err.c
    viewer_view/QtGifImage/giflib/gif_font.c
    viewer_view/QtGifImage/giflib/gif_hash.c
    viewer_view/QtGifImage/giflib/gif_hash.h
    viewer_view/QtGifImage/giflib/gif_lib.h
    viewer_view/QtGifImage/giflib/gif_lib_private.h
    viewer_view/QtGifImage/giflib/gifalloc.c
    viewer_view/QtGifImage/giflib/quantize.c
)

target_link_libraries(3D_Viewer Qt6::Widgets Qt6::Core)
target_link_libraries(3D_Viewer Qt6::Charts Qt6::Core)
