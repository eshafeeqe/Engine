cmake_minimum_required (VERSION 3.9)

project(ImGui)

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}/ImGui")

add_library(ImGui STATIC  "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imconfig.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_draw.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_internal.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_widgets.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imstb_rectpack.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imstb_textedit.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imstb_truetype.h"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_demo.cpp"
                          "${CMAKE_CURRENT_SOURCE_DIR}/ImGui/imgui_tables.cpp")

set_target_properties(ImGui PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set_property(TARGET ImGui PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(ImGui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


