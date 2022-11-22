cmake_minimum_required (VERSION 3.9)

project(Engine VERSION 1.0.1 DESCRIPTION "Engine description")

SET (CMAKE_C_FLAGS_INIT                "-Wall")
SET (CMAKE_C_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_C_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_C_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

SET (CMAKE_CXX_FLAGS_INIT                "-Wall")
SET (CMAKE_CXX_STANDARD                   14)
SET (CMAKE_CXX_FLAGS_DEBUG_INIT          "-g")
SET (CMAKE_CXX_FLAGS_MINSIZEREL_INIT     "-Os -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELEASE_INIT        "-O3 -DNDEBUG")
SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")


SET(ENGINE_SRCS_PATH     "${PROJECT_SOURCE_DIR}/Engine/src")
SET(SPDLOG_INCLUDE_PATH  "${PROJECT_SOURCE_DIR}/Engine/vendor/spdlog/include")

add_subdirectory(${PROJECT_SOURCE_DIR}/Engine/vendor/glfw)
add_subdirectory(${PROJECT_SOURCE_DIR}/Engine/vendor/Glad)

INCLUDE_DIRECTORIES(${SPDLOG_INCLUDE_PATH})

FILE(GLOB_RECURSE ENGINE_SRCS "${ENGINE_SRCS_PATH}/*.cpp")

ADD_LIBRARY(Engine SHARED ${ENGINE_SRCS} $<TARGET_OBJECTS:GLFW> $<TARGET_OBJECTS:Glad>)

set_target_properties(Engine PROPERTIES
         LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Engine)

target_include_directories(Engine PUBLIC ${ENGINE_SRCS_PATH} ${SPDLOG_INCLUDE_PATH})
target_link_libraries(Engine PUBLIC pthread dl)

set(SANDBOX_SRCS_PATH  "${PROJECT_SOURCE_DIR}/Sandbox/src")
file(GLOB_RECURSE SANDBOX_SRCS "${SANDBOX_SRCS_PATH}/*.cpp" "${SANDBOX_SRCS_PATH}/*.h")

message("${SANDBOX_SRCS}")

add_executable(Sandbox ${SANDBOX_SRCS})

set_target_properties(Sandbox PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Sandbox)
target_include_directories(Sandbox PUBLIC ${ENGINE_SRCS_PATH})
target_link_libraries(Sandbox PUBLIC Engine)

set_target_properties(Sandbox PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/Sandbox)
