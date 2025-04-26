cmake_minimum_required(VERSION 3.14)
project(tactical_monsters)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

configure_file(${CMAKE_SOURCE_DIR}/splash.jpg ${CMAKE_BINARY_DIR}/splash.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/bg.png ${CMAKE_BINARY_DIR}/bg.png COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/polyg.jpg ${CMAKE_BINARY_DIR}/polyg.jpg COPYONLY)
configure_file(${CMAKE_SOURCE_DIR}/polyg.png ${CMAKE_BINARY_DIR}/polyg.png COPYONLY)

add_executable(tactical_monsters
    main.cpp
    splash.cpp
    splash.h
    mainwindow.cpp
    mainwindow.h
    gameboard.h gameboard.cpp
)

target_link_libraries(tactical_monsters Qt6::Core Qt6::Gui Qt6::Widgets)
