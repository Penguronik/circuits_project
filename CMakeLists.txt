cmake_minimum_required(VERSION 3.16)

project(circuits_project VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_executable(circuits_project
    Backend/circuitcomponent.h Backend/circuitcomponent.cpp
    Backend/componenttreeitem.h Backend/componenttreeitem.cpp
    Backend/componenttreemodel.h Backend/componenttreemodel.cpp
    Backend/pinbase.h Backend/pinbase.cpp
    Backend/pinin.h Backend/pinin.cpp
    Backend/pinout.h Backend/pinout.cpp
    Backend/wire.h Backend/wire.cpp
    Backend/components.cpp 
    Backend/gates.cpp
    Frontend/constants.h
    Frontend/graphicscircuitcomponent.h Frontend/graphicscircuitcomponent.cpp
    Frontend/graphicscomponents.h Frontend/graphicscomponents.cpp
    Frontend/graphicsgates.h Frontend/graphicsgates.cpp
    Frontend/graphicspinbase.h Frontend/graphicspinbase.cpp
    Frontend/graphicspinin.h Frontend/graphicspinin.cpp
    Frontend/graphicspinout.h Frontend/graphicspinout.cpp
    Frontend/graphicswire.h Frontend/graphicswire.cpp
    Frontend/mainwindow.h Frontend/mainwindow.cpp
    Frontend/scene.h Frontend/scene.cpp
    Frontend/view.h Frontend/view.cpp
    Frontend/main.cpp
)

target_include_directories(circuits_project PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Backend" PUBLIC "${CMAKE_CURRENT_LIST_DIR}/Frontend" PUBLIC "${CMAKE_CURRENT_LIST_DIR}")

target_link_libraries(circuits_project PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets gpiod)

# resources:
set(resource_files
    "icons/not-gate.png"
    "icons/trash-solid.png"
    "icons/folder-solid.png"
    "icons/hand-paper-solid.png"
    "icons/object-group-solid.png"
)

qt_add_resources(circuits_project "resources"
    PREFIX
        "/"
    FILES
        ${resource_files}
)

set_target_properties(circuits_project PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
