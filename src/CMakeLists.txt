cmake_minimum_required(VERSION 3.10)
project(guiextension VERSION 1.0.0)

set(PRODUCTNAME "GuiExtension Library")
set(DESCRIPTION "GuiExtension Library")
set(COMPANY     "RTPTechGroup")
set(COPYRIGHT   "Copyright (C) RTPTechGroup")

include("${CMAKE_SOURCE_DIR}/cmake/libs.cmake")

target_compile_definitions(${PROJECT_NAME} PRIVATE -DGUIEXTENSION_LIBRARY)

find_package(Qt5Core)
target_link_libraries(${PROJECT_NAME} Qt5::Core)

find_package(Qt5Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
