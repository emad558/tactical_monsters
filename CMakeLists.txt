cmake_minimum_required(VERSION 3.14)
project(tactical_monsters)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

configure_file(${CMAKE_SOURCE_DIR}/image/splash.jpg ${CMAKE_BINARY_DIR}/image/splash.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/bg.jpg ${CMAKE_BINARY_DIR}/image/bg.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/p1.jpg ${CMAKE_BINARY_DIR}/image/p1.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/p2.jpg ${CMAKE_BINARY_DIR}/image/p2.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/rock.jpg ${CMAKE_BINARY_DIR}/image/rock.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/water.jpg ${CMAKE_BINARY_DIR}/image/water.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/polyg.png ${CMAKE_BINARY_DIR}/image/polyg.png COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/image/a1.jpg ${CMAKE_BINARY_DIR}/image/a1.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/a2.jpg ${CMAKE_BINARY_DIR}/image/a2.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/a3.jpg ${CMAKE_BINARY_DIR}/image/a3.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/a4.jpg ${CMAKE_BINARY_DIR}/image/a4.jpg COPYONLY)

configure_file(${CMAKE_SOURCE_DIR}/image/highlight.jpg ${CMAKE_BINARY_DIR}/image/highlight.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/image/place_highlight.jpg ${CMAKE_BINARY_DIR}/image/place_highlight.jpg COPYONLY)


add_executable(tactical_monsters
    main.cpp
    splash.cpp
    splash.h
    mainwindow.cpp
    mainwindow.h
    gameboard.h gameboard.cpp
    clickabletile.h clickabletile.cpp
    gallerywindow.h gallerywindow.cpp
)

target_link_libraries(tactical_monsters Qt6::Core Qt6::Gui Qt6::Widgets)
