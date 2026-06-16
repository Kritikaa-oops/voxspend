cmake_minimum_required(VERSION 3.16)

project(VoxSpend VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick QuickControls2)

set(PROJECT_SOURCES
    src/main.cpp
    src/database/json_storage.cpp
    src/database/json_storage.h
    src/controllers/expense_manager.cpp
    src/controllers/expense_manager.h
    src/models/expense_item.cpp
    src/models/expense_item.h
    ui/qml.qrc
)

qt_add_executable(VoxSpend
    ${PROJECT_SOURCES}
)

target_include_directories(VoxSpend PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(VoxSpend PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Quick
    Qt6::QuickControls2
)
