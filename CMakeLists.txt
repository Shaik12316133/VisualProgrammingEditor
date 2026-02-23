cmake_minimum_required(VERSION 3.16)

project(VisualNodeEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_add_executable(VisualNodeEditor
    main.cpp

    MainWindow.h
    MainWindow.cpp

    GraphView.h
    GraphView.cpp

    NodeItem.h
    NodeItem.cpp

    PinItem.h
    PinItem.cpp

    WireItem.h
    WireItem.cpp

    ExecutionEngine.h
    ExecutionEngine.cpp
    minimap.h minimap.cpp
    variablesystem.h variablesystem.cpp
    nodetypes.h
)

target_link_libraries(VisualNodeEditor PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
