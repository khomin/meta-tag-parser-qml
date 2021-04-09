cmake_minimum_required(VERSION 3.1.0)

set(PROJECT_NAME "meta_html_parser")

project(${PROJECT_NAME} VERSION 0.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Core Gui Qml Quick QuickControls2 REQUIRED)

qt5_add_resources(RESOURCES qml.qrc)

include_directories(
    ${Qt5Widgets_INCLUDE_DIRS}
    ${QtQml_INCLUDE_DIRS}
    ./../source/
    ./../source/meta_parser/
)

add_definitions(${Qt5Widgets_DEFINITIONS} ${QtQml_DEFINITIONS} ${${Qt5Quick_DEFINITIONS}})

add_executable(${PROJECT_NAME}
    ./main.cpp
    ./source/meta_parser/file_download.cpp
    ./source/meta_parser/handle_input.cpp
    ./source/meta_parser/og_parser.cpp
    ./source/model_input_line.cpp
    ${RESOURCES}
)

target_link_libraries(${PROJECT_NAME}
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::Quick
)
