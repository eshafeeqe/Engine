cmake_minimum_required (VERSION 3.9)

project(Glad C)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(Glad STATIC "${CMAKE_CURRENT_SOURCE_DIR}/include/glad/glad.h"
                        "${CMAKE_CURRENT_SOURCE_DIR}/include/KHR/khrplatform.h"
                        "${CMAKE_CURRENT_SOURCE_DIR}/src/glad.c")

set_target_properties(Glad PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set_property(TARGET Glad PROPERTY POSITION_INDEPENDENT_CODE ON)

target_include_directories(Glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


